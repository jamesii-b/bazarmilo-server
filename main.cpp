#include <iostream>
#include "./headers/httplib.h"

#include "./headers/dbConnection.h"

int main(int argc, char **argv)

{
    sqlite3 *DB;
    dbConnection(DB);

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
            { res.set_content("Salut~", "text/plain"); });
    svr.listen("localhost", 8080);
    closeConnection(DB);
    return 0;
}