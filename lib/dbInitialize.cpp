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
                                 "contactnum VARCHAR(255) NOT NULL,"
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

void initializeVehicleTable(sqlite3 *DB)
{
    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS vehicles ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "vehicleNumber VARCHAR(255) NOT NULL,"
                                 "vehicleOwner VARCHAR(255) NOT NULL"
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
        std::cout << "Table 'vehicles' created successfully!" << std::endl;
    }
}

void initializeProductTaskTable(sqlite3 *DB)
{
    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS productTasks ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "productID VARCHAR(255) NOT NULL,"
                                 "username VARCHAR(255) NOT NULL,"
                                 "vehicleNumber VARCHAR(255) NOT NULL,"
                                 "latitudeFrom DECIMAL(9,6) NOT NULL,"
                                 "longitudeFrom DECIMAL(9,6) NOT NULL,"
                                 "latitudeTo DECIMAL(9,6) NOT NULL,"
                                 "longitudeTo DECIMAL(9,6) NOT NULL,"
                                 "date DATE NOT NULL,"
                                 "delivered INTEGER DEFAULT 0,"
                                 "FOREIGN KEY (vehicleNumber) REFERENCES vehicles(vehicleNumber),"
                                 "FOREIGN KEY (username) REFERENCES users(username)"
                                 ");";

    char *errMsg = nullptr;
    int result = sqlite3_exec(DB, createTableSQL.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error during productTask table creation: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Table 'productTask' created successfully!" << std::endl;
    }
}