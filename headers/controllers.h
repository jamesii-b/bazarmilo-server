#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <sqlite3.h>
#include "../headers/httplib.h"
#include "json.hpp"
// Function declarations
void adminRegisterDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);
void adminLoginDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);

void userLoginDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);
void userRegisterDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);
/* get datum with id*/
void userDatum(std::string id, httplib::Response &res, sqlite3 *DB);

void createVehicles(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);
void getVehicles(httplib::Response &res, sqlite3 *DB);

void createTask(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);
void updateTask(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB);
void getTasks(httplib::Response &res, sqlite3 *DB);

#endif