#include "../headers/controllers.h"
#include "../headers/json.hpp"
#include "../headers/httplib.h"
#include "../headers/dbInitialization.h"
#include <iostream>
#include "../headers/json.hpp"

void getVehicles(httplib::Response &res, sqlite3 *DB)
{
    initializeVehicleTable(DB);
    std::string command = "SELECT * FROM vehicles;";
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK)
    {
        res.status = 500; // Internal Server Error
        res.set_content("SQL prepare error: " + std::string(sqlite3_errmsg(DB)), "text/plain");
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        nlohmann::json resultJson;

        // Execute the statement in a loop
        while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            nlohmann::json row;
            for (int i = 0; i < sqlite3_column_count(stmt); ++i)
            {
                // Assuming all columns are strings for simplicity, you might need to handle different types
                const char *columnName = sqlite3_column_name(stmt, i);
                const char *columnValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i));
                row[columnName] = columnValue;
            }
            resultJson.push_back(row);
        }

        if (result != SQLITE_DONE)
        {
            res.status = 500; // Internal Server Error
            res.set_content("SQL execution error: " + std::string(sqlite3_errmsg(DB)), "text/plain");
            std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
        }
        else
        {
            res.status = 200; // OK
            res.set_content(resultJson.dump(), "application/json");
            std::cout << "Query executed successfully!" << std::endl;
        }

        sqlite3_finalize(stmt);
    }
}

void createVehicles(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB)
{
    initializeVehicleTable(DB);
    std::string vehicleNumber = data["vehicleNumber"];
    std::string vehicleOwner = data["vehicleOwner"];
    std::string command = "INSERT into vehicles (vehicleNumber, vehicleOwner) VALUES (?, ?);";

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK)
    {
        res.status = 404;
        res.set_content("Registration failed", "text/plain");
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        sqlite3_bind_text(stmt, 1, vehicleNumber.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, vehicleOwner.c_str(), -1, SQLITE_STATIC);

        result = sqlite3_step(stmt);

        if (result != SQLITE_DONE)
        {
            res.status = 404;
            res.set_content("Vehicle Registration failed", "text/plain");
            std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
        }
        else
        {
            res.status = 200;
            res.set_content("Vehcile Registration successful", "text/plain");
            std::cout << "Record inserted successfully!" << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    std::cout << "vehiclenumber: " << vehicleNumber << std::endl;
    std::cout << "vehicleowner: " << vehicleOwner << std::endl;
}