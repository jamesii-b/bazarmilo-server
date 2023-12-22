// header/dbConnection.h

#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <sqlite3.h>

void dbConnection(sqlite3 *&DB);
void closeConnection(sqlite3 *DB);

#endif
