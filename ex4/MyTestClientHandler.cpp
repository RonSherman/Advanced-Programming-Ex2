//
// Created by amitnir29 on 17/01/2020.
//

#include "MyTestClientHandler.h"
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
using namespace std;
int MyTestClientHandler::handleClient(int socket){
	char buffer[1024];
	//read the data
	while (strcmp(buffer, "end") != 0) {
		int valread = read(socket, buffer, 1024);
		//delete the \n
		string line = std::string(buffer);
		//std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
		//line.erase(end_pos, line.end());
		//buffer[strlen(buffer) - 1] = '\0';
		if(line.find('\r') != string::npos)
			line = line.substr(0, line.find('\r'));
		if (line.find('\n') != string::npos)
			line = line.substr(0, line.find('\n'));
		cout << "got from client:" << line << endl;
		//cout << "==================" << endl;
		//if has sol, return it
		if (this->cm->hasSolution(line)) {
			//Solution sol = this->cm->getSolution(buffer);
			std::string str = this->cm->getSolution(line);
			cout << "sent to client-" << str << endl;
			//std::string str = Solution::toString();
			str = str.append("\n");
			send(socket, str.c_str(), strlen(str.c_str()), 0);
			cout << "used solution found" << endl;
		}
		//else, calc solve.solve(input), cache it and return output
		else {
			std::string str = this->s->solve(line);
			cout << "sent to client-" << str << endl;
			//save the solution to the cache
			this->cm->setSolution(line, str);
			str=str.append("\n");
			//std::string str = Solution::toString();
			send(socket, str.c_str(), strlen(str.c_str()), 0);
			cout << "new solution generated" << endl;
		}
	}
	//close the client
	close(socket);
};