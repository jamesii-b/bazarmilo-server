#include "../headers/controllers.h"
#include "../headers/json.hpp"
#include "../headers/httplib.h"
#include <iostream>

void userLoginDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB)
{
    std::string username = data["username"];
    std::string password = data["password"];
    std::string command = "SELECT * FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK)
    {
        res.set_content("Database error", "text/plain");
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW)
    {
        res.status = 200;
        res.set_content("Authentication successful", "text/plain");
    }
    else
    {
        res.status = 404;
        res.set_content("Authentication failed", "text/plain");
    }

    sqlite3_finalize(stmt);
}
