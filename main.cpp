// main.cpp
#include <iostream>
#include <thread>
#include "./headers/httplib.h"
#include "./headers/dbConnection.h"
#include "./headers/dbInitialization.h"
#include "./headers/json.hpp"
#include <sqlite3.h>
#include "./headers/controllers.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

sqlite3 *DB; // Declare a global variable for database connection

typedef websocketpp::server<websocketpp::config::asio> WebSocketServer;
WebSocketServer broadcastServer;
std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> con_list;

void on_message(websocketpp::connection_hdl hdl, WebSocketServer::message_ptr msg)
{
    try
    {
        nlohmann::json j = nlohmann::json::parse(msg->get_payload());
        std::cout << "Location update received from mobile app\n\n"
                  << j << std::endl;

        // Iterate through all connections and send the message to each one
        for (auto it : con_list)
        {
            broadcastServer.send(it, msg->get_payload(), websocketpp::frame::opcode::text);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}

void on_open(websocketpp::connection_hdl hdl)
{
    con_list.insert(hdl);
}

void on_close(websocketpp::connection_hdl hdl)
{
    con_list.erase(hdl);
}

void runWebSocketServer()
{
    try
    {
        WebSocketServer ws_svr;
        ws_svr.set_open_handler(&on_open);
        ws_svr.set_close_handler(&on_close);
        ws_svr.set_message_handler(&on_message);
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
    std::thread websocketThread(runWebSocketServer);
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

    svr.Post("/task/create", [&](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        createTask(j, res, DB); });
    svr.Post("/task/update", [&](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        updateTask(j, res, DB); });

    svr.Get("/tasks", [&](const httplib::Request &req, httplib::Response &res)
            { getTasks(res, DB); });

    try
    {
        svr.listen("0.0.0.0", 8080);
        websocketThread.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
    closeConnection(DB);
    return 0;
}
