//
// Created by amitnir29 on 17/01/2020.
//

#include "MySerialServer.h"
#include "interfaces.h"
#include <stdio.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <iostream>
using namespace std;
int MySerialServer::open(int port, client_handler::ClientHandler* c) {
	cout << "opened" <<endl;
	/*//creating a socket
	int sockid = socket(AF_INET, SOCK_STREAM, 0);
	if (sockid == -1) {
		std::cout << "error in openserver socket" << std::endl;
		exit(1);
	}
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
	if (listen(sockid, 5) == -1) {
		cout << "listening my serial server failed" << endl;
		exit(1);
	}
	this->openedConn = true;*/
	//create a listener for a client
	std::thread thr(&MySerialServer::startClientsPartB,this,port,c);
	thr.join();
	//while (this->openedConn) {
	//}
	//while this server is listening, get a client
	/*while (this->openedConn) {
		//accept the client
		int client_socket = accept(sockid, (struct sockaddr *) &address, (socklen_t*)&addrlen);
		if (client_socket == -1) {
			cout << "client_socket my serial server  failed" << endl;
			exit(1);
		}
		//hadnle it- this is a blocking call, until we get a 'end'
		c->handleClient(client_socket);
	}
	using namespace std::chrono;
	// Get starting timepoint 
	auto start = std::chrono::high_resolution_clock::now();
	//hold until connection is made, for ten seconds
	//while (!this->openedConn || duration_cast<seconds>(high_resolution_clock::now()-start).count() < 10) {

	//}
	//detach the thread from the current function
	//in another thread-
	//bind to port
	//open conn
	//accept someone, wait for timeout seconds
	//do c.handle(recv,string)
	//send the string to the client reversed
	*/
    return 0;
}
//TODO- timeout timer
void MySerialServer::startClientsPartB(int port, client_handler::ClientHandler* c) {
	cout << "got here" << endl;
	//creating a socket
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
		cout << "listening my serial server failed" << endl;
		exit(1);
	}
	cout << "started listening on server " << endl;
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
		c->handleClient(client_socket);
		//if we got a client, reset the timer
		//start = std::chrono::high_resolution_clock::now();
	}
	this->closeServer();
	close(sockid);
}
int MySerialServer::closeServer() {
	this->openedConn = false;
	//close(sockid);
    return 0;
}

MySerialServer::MySerialServer() {}
