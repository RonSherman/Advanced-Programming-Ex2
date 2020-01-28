
//
// Created by amitnir29 on 27/01/2020.
//

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "MyParallelServer.h"

int MyParallelServer::open(int port, client_handler::ClientHandler *c) {
    this->port = port;

    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    if (sockid == -1) {
        std::cout << "error in openserver socket" << std::endl;
        exit(1);
    }
    struct timeval tv;
    tv.tv_sec = 120;
    setsockopt(sockid, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    //open connection to server
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  //or INADDR_ANY
    address.sin_port = htons(port);


    int addrlen = sizeof(address);
    //bidning socket
    if (bind(sockid, (struct sockaddr *) &address, sizeof(address)) == -1) {
        exit(1);
    }
    //listening
    if (listen(sockid, 10) == -1) {
        cout << "listening my parallel server failed" << endl;
        exit(1);
    }
    //cout << "started listening on server " << endl;
    using namespace std::chrono;
    //auto start = std::chrono::high_resolution_clock::now();
    this->openedConn = true;
    //while this server is listening, get a client
    while (this->openedConn) {
        //accept the client
        //if (duration_cast<seconds>(high_resolution_clock::now() - start).count() < 10) {

        int client_socket = accept(sockid, (struct sockaddr *) &address, (socklen_t*)&addrlen);
        if (client_socket == -1) {
            cout << "client_socket my serial server- timeout or failed" << endl;
            exit(1);
        }
        //}
        //hadnle it- this is a blocking call, until we get a 'end'
        clients.push_back(new thread(&client_handler::ClientHandler::handleClient, c, client_socket));
        //if we got a client, reset the timer
        //start = std::chrono::high_resolution_clock::now();
    }

    list<thread*> v = list<thread*>(clients);

    for (auto client : v) {
        client->join();
        clients.remove(client);
    }

    this->closeServer();
    close(sockid);

}

int MyParallelServer::closeServer() {
    this->openedConn = false;
    //close(sockid);
    return 0;
}
