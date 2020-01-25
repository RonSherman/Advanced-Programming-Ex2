//
// Created by amitnir29 on 17/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "interfaces.h"
using namespace server_side;
class MySerialServer : public Server {
	bool openedConn=false;
public:
    MySerialServer();

    int open(int port, client_handler::ClientHandler* c) override;
	void startClientsPartB(int port, client_handler::ClientHandler* c);
    int closeServer() override;

};


#endif //EX4_MYSERIALSERVER_H
