#include "../headers/controllers.h"
#include "../headers/json.hpp"
#include "../headers/httplib.h"
#include <iostream>

void userDatum(std::string id, httplib::Response &res, sqlite3 *DB)
{
    std::string command = "SELECT * FROM users WHERE id = ?;";
    sqlite3_stmt *stmt;

    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK)
    {
        res.set_content("Database error", "text/plain");
        return;
    }

    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW)
    {
        nlohmann::json jsonData;

        int columns = sqlite3_column_count(stmt);

        for (int i = 0; i < columns; ++i)
        {
            const char *columnName = sqlite3_column_name(stmt, i);
            const char *columnValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i));

            // Add column name and value to the JSON object
            jsonData[columnName] = columnValue;
        }

        res.status = 200;
        res.set_content(jsonData.dump(), "application/json");
    }
    else
    {
        res.status = 404;
        res.set_content("Data retrieval failed", "text/plain");
    }

    sqlite3_finalize(stmt);
}
