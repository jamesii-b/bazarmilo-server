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
#endif
