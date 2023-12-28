# Bazarmilo Server
This is the server for the Bazarmilo Project. This project uses the framework `httplib` used as `httplib.h` & database `sqlite3`.

## How to run
- g++ main.cpp  -l sqlite3
```
If you haven't installed sqlite3 you should first install sqlite3.
```
Command to install `sqlite3` on `Debian` based systems:
```
sudo apt-get update && sudo apt-get install sqlite3 libsqlite3-dev
```

## Dependencies
- `sqlite3`
- `httplib`
- [`nlohmann/json`]("https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp")
## Authors
- [`@jamesii-b`]


## SQLITE3

### Perform CRUD operation in CLI

```
.tables```

```
CREATE TABLE users ( id INTEGER PRIMARY KEY,
    username VARCHAR(255),
    password VARCHAR(255));```
```
sqlite> PRAGMA table_info(users);
0|id|INTEGER|0||1
1|username|VARCHAR(255)|0||0
2|password|VARCHAR(255)|0||0
```