#include "../headers/dbInitialization.h"
#include <iostream>
#include <sqlite3.h>
#include <cstdlib> // for exit and EXIT_FAILURE

void initializeadmintable(sqlite3 *DB)
{
    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS admins ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "username TEXT NOT NULL,"
                                 "password TEXT NOT NULL);";

    char *errMsg = nullptr;
    int result = sqlite3_exec(DB, createTableSQL.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error during table creation: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Table 'admins' created successfully!" << std::endl;
    }
}

void initializeusertable(sqlite3 *DB)
{

    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS users ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "username VARCHAR(255) NOT NULL,"
                                 "password VARCHAR(255) NOT NULL,"
                                 "fullname TEXT NOT NULL,"
                                 "licensenum VARCHAR(255) NOT NULL"
                                 ");";

    char *errMsg = nullptr;
    int result = sqlite3_exec(DB, createTableSQL.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error during table creation: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Table 'users' created successfully!" << std::endl;
    }
}