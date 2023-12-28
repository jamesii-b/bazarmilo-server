#include <iostream>
#include "./headers/httplib.h"

#include "./headers/dbConnection.h"
#include "./headers/dbInitialization.h"
#include "./headers/json.hpp"

int main(int argc, char **argv)

{
    sqlite3 *DB;
    dbConnection(DB);

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
            { res.set_content("Salut~", "text/plain"); });

    svr.Post("/admin/login", [&](const httplib::Request &req, httplib::Response &res)
             {
                 nlohmann::json j = nlohmann::json::parse(req.body);
                 std::string username = j["username"];
                 std::string password = j["password"];
                 std::string command = "SELECT * FROM admins WHERE username = ? AND password = ?;";
                 sqlite3_stmt *stmt;
                 int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);
                 if (result != SQLITE_OK)
                 {
                     // Handle error
                     res.set_content("Database error", "text/plain");
                     return;
                 }

                 // Bind parameters
                 sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
                 sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

                 // Execute the query
                 result = sqlite3_step(stmt);

                 if (result == SQLITE_ROW)
                 {
                     // Authentication successful
                     res.set_content("Authentication successful", "text/plain");
                 }
                 else
                 {
                     // Authentication failed
                     res.set_content("Authentication failed", "text/plain");
                 }
                 /*    std::cout << req.body << std::endl;
                    res.set_content("ok", "text/plain");
                     */ });

    svr.Post("/user/register", [&](const httplib::Request &req, httplib::Response &res)
             {
    try {
        initializeusertable(DB);
        nlohmann::json j = nlohmann::json::parse(req.body);
        std::string name = j["fullname"];
        std::string licensenum = j["licensenum"];
        std::string username = j["username"];
        std::string password = j["password"];
        std::string command = "INSERT INTO users (username, password, licensenum, fullname) VALUES (?, ?, ?, ?);";

        sqlite3_stmt *stmt;
        int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
        } else {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, licensenum.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(stmt);

            if (result != SQLITE_DONE) {
                std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
            } else {
                std::cout << "Record inserted successfully!" << std::endl;
            }

            // Finalize the statement
            sqlite3_finalize(stmt);
        }

        std::cout << "Username: " << username << std::endl;
        std::cout << "Name: " << name << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    } });

    svr.Post("/admin/register", [&](const httplib::Request &req, httplib::Response &res)
             {
    try {
        initializeadmintable(DB);
        nlohmann::json j = nlohmann::json::parse(req.body);
        std::string username = j["username"];
        std::string password = j["password"];
        std::string command = "INSERT INTO admins (username, password) VALUES (?, ?);";

        sqlite3_stmt *stmt;
        int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK) {
            std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
        } else {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(stmt);

            if (result != SQLITE_DONE) {
                std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
            } else {
                std::cout << "Record inserted successfully!" << std::endl;
            }

            // Finalize the statement
            sqlite3_finalize(stmt);
        }

        std::cout << "Username: " << username << std::endl;
        std::cout << "pass: " << password << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    } });

    svr.listen("localhost", 8080);
    closeConnection(DB);
    return 0;
}