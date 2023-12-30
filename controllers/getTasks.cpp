#include "../headers/controllers.h"
#include "../headers/json.hpp"
#include "../headers/httplib.h"
#include "../headers/dbInitialization.h"
#include <iostream>

void getTasks(httplib::Response &res, sqlite3 *DB)
{

    initializeProductTaskTable(DB);
    std::string command = "SELECT * FROM productTasks;";
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