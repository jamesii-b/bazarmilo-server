# Bazarmilo Logistics System 

## Overview
This project is a comprehensive logistics system designed to streamline operations and enhance efficiency. It consists of a robust web server developed in C++. The system incorporates real-time tracking features powered by OpenStreetMap (OSM), user authentication for security, and dynamic task management capabilities.

## Dependencies
- `sqlite3`
- `httplib`
- [`nlohmann/json`]("https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp")
- [`websocketpp`]("https://github.com/zaphoyd/websocketpp.git")


## 🌟 Features
- **Real-time Tracking**: Utilizes OpenStreetMap for accurate and up-to-date location tracking.
- **User Authentication**: Secure access control to ensure data privacy and integrity.
- **Task Management**: Enables users to create, update, and monitor tasks in real-time.
- **Mobile Integration**: Companion Flutter mobile app for on-the-go access and management.

## 💻 Technologies
- **Backend**: C++ for the web server, integrating with SQLite3 for database management.
- **Frontend**: Flutter framework for cross-platform mobile development.
- **Mapping**: Integration with OpenStreetMap for geospatial functionality.
- **Networking**: Utilizes httplib for handling HTTP requests and WebSocket communication.


## 🚀 How to Use
1. Clone the repository to your local machine.
```
git clone https://github.com/zaphoyd/websocketpp.git && cd websocketpp && mkdir build && cd build && sudo apt install cmake -y && cmake .. && make && sudo make install
```
2.  Set up the necessary dependencies for the C++ server 

```
sudo apt-get update && sudo apt-get install sqlite3 libsqlite3-dev
```
```
git clone https://github.com/zaphoyd/websocketpp.git && cd websocketpp && mkdir build && cd build && sudo apt install cmake -y && cmake .. && make && sudo make install
```
3. Run the C++ server and deploy the Flutter app to your preferred mobile device or emulator.
```
 g++ main.cpp  -l sqlite3 && ./a.out
```

4. Access the system through the provided interfaces and explore the features.

## 🤝 Contributing
Contributions are welcome! If you'd like to contribute to this project, please follow the standard guidelines for pull requests and issue reporting.

## 📧 Contact
For inquiries or support, feel free to contact  [jamesii-b](https://github.com/jamesii-b).

