// header/dbInitialization.h

#ifndef DBINITIALIZE_H
#define DBINITIALIZE_H

#include <sqlite3.h>

void initializeadmintable(sqlite3 *DB);
void initializeusertable(sqlite3 *DB);

#endif