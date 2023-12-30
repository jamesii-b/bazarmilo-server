#include "../headers/controllers.h"
#include "../headers/json.hpp"
#include "../headers/httplib.h"
#include "../headers/dbInitialization.h"
#include <iostream>

void createTask(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB)
{
    initializeProductTaskTable(DB);

    std::string username = data["username"];
    std::string productID = data["productID"];
    std::string vehicleNumber = data["vehicleNumber"]; // Fixed the typo in the key "vehicleNumer"
    std::string latitudeFrom = data["latitudeFrom"];
    std::string longitudeFrom = data["longitudeFrom"];
    std::string latitudeTo = data["latitudeTo"];
    std::string longitudeTo = data["longitudeTo"];
    std::string date = data["date"];

    std::string command = "INSERT INTO productTasks (username, productID, vehicleNumber, latitudeFrom, longitudeFrom, latitudeTo, longitudeTo, date) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK)
    {
        res.status = 404;
        res.set_content("Task creation failed", "text/plain");
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, productID.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, vehicleNumber.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, latitudeFrom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, longitudeFrom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, latitudeTo.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, longitudeTo.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, date.c_str(), -1, SQLITE_STATIC);

        result = sqlite3_step(stmt);

        if (result != SQLITE_DONE)
        {
            res.status = 404;
            res.set_content("Task creation failed", "text/plain");
            std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
        }
        else
        {
            res.status = 200;
            res.set_content("Task created successfully", "text/plain");
            std::cout << "Task inserted successfully!" << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    std::cout << "Username: " << username << std::endl;
    std::cout << "Product ID: " << productID << std::endl;
}

void updateTask(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB)
{
    std::string productID = data["productID"];
    int delivered = data["delivered"];
    if (delivered != 1 && delivered != 0)
    {
        res.status = 404;
        res.set_content("Task update failed", "text/plain");
        std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
        return;
    }
    std::string command = "UPDATE productTasks SET delivered = ? WHERE productID = ?;";
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK)
    {
        res.status = 404;
        res.set_content("Task creation failed", "text/plain");
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        sqlite3_bind_int(stmt, 1, delivered);
        sqlite3_bind_text(stmt, 2, productID.c_str(), -1, SQLITE_STATIC);

        result = sqlite3_step(stmt);

        if (result != SQLITE_DONE)
        {
            res.status = 404;
            res.set_content("Task update failed", "text/plain");
            std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
        }
        else
        {
            res.status = 200;
            if (delivered == 1)
                res.set_content("Task update of `delivered` successfully", "text/plain");
            else
            {

                res.set_content("Task update of `undelivered` successfully", "text/plain");
            }
            std::cout << "Task inserted successfully!" << std::endl;
        }

        sqlite3_finalize(stmt);
    }
}
