#include "interfaces.h"
#include <string>
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include <iostream>
int main(int argc, char* argv[]) {
	problem_solving::Solver< std::string, std::string>* sol = new StringReverser();
	FileCacheManager* cm = new FileCacheManager();
	MyTestClientHandler* handle = new MyTestClientHandler(sol, cm);

	server_side::Server* server = new MySerialServer();
	using namespace std;
	cout << "started server" << endl;
	server->open(atoi(argv[1]), handle);
	//server->open(5600, handle);
	return 0;
}