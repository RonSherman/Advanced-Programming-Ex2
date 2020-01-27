//
// Created by amitnir29 on 27/01/2020.
//

#ifndef MITKADEMEX4_MYPARALLELSERVER_H
#define MITKADEMEX4_MYPARALLELSERVER_H


#include "interfaces.h"
#include <list>
#include <thread>

using namespace std;
class MyParallelServer : public server_side::Server {

    bool openedConn = false;
    int port;
    list<thread*> clients;

public:
    int open(int port, client_handler::ClientHandler *c) override;

    int closeServer() override;
};


#endif //MITKADEMEX4_MYPARALLELSERVER_H
