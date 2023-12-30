// main.cpp
#include <iostream>
#include <thread>
#include "./headers/httplib.h"
#include "./headers/dbConnection.h"
#include "./headers/dbInitialization.h"
#include "./headers/json.hpp"
#include <sqlite3.h>
#include "./headers/controllers.h"

sqlite3 *DB; // Declare a global variable for database connection
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> WebSocketServer;

// ...

// Initialize WebSocket server

// Define a handler for incoming WebSocket messages
void on_message(websocketpp::connection_hdl hdl, WebSocketServer::message_ptr msg)
{
    try
    {
        nlohmann::json j = nlohmann::json::parse(msg->get_payload());
        // Handle location update received from mobile app
        // You can parse the JSON message and store/update the location data in your C++ server
        // Example: Update location in a data structure or database
        std::cout << "Location update received from mobile app \n \n"
                  << j << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}

// WebSocket endpoint to receive location updates from the mobile app

void runwebSocketServer()
{
    try
    {
        WebSocketServer ws_svr;
        ws_svr.set_message_handler(on_message);

        // WebSocket endpoint for the desktop application to connect and receive location updates
        ws_svr.init_asio();
        ws_svr.listen(8081);
        ws_svr.start_accept();
        ws_svr.run();
    }

    catch (const std::exception &e)
    {
        std::cerr << "WebSocket server error: " << e.what() << std::endl;
    }
}

int main(int argc, char **argv)
{

    // WebSocket endpoint for the desktop application to connect and receive location updates
    std::thread websocketThread(runwebSocketServer);

    // Start WebSocket server

    dbConnection(DB);

    httplib::Server svr;

    // Routes
    svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
            { res.set_content("hello~", "text/plain"); });
    svr.Get("/ws", [&](const httplib::Request &req, httplib::Response &res)
            {
                res.set_content("WebSocket connection established", "text/plain");
                // You can send location updates to the desktop application here
            });

    svr.Post("/admin/login", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        adminLoginDB(j, res,DB); });

    svr.Post("/admin/register", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        adminRegisterDB(j, res,DB); });

    svr.Post("/user/login", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        userLoginDB(j, res,DB); });

    svr.Post("/user/register", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        userRegisterDB(j, res,DB); });
    svr.Get("/user/travel/:id", [&](const httplib::Request &req, httplib::Response &res)
            {
    auto ID = req.path_params.at("id");
                res.set_content("Database error", "text/plain");
                std::cout << ID << std::endl; });

    svr.Get("/user/datum/:id", [&](const httplib::Request &req, httplib::Response &res)
            {
    auto ID = req.path_params.at("id");
    userDatum(ID, res, DB); });

    svr.Get("/vehicles", [&](const httplib::Request &req, httplib::Response &res)
            { getVehicles(res, DB); });
    svr.Post("/vehicle/register", [&](const httplib::Request &req, httplib::Response &res)

             { 
    nlohmann::json j = nlohmann::json::parse(req.body);
                createVehicles(j, res, DB); });

    try
    {
        svr.listen("localhost", 8080);
        websocketThread.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
    closeConnection(DB);
    return 0;
}
