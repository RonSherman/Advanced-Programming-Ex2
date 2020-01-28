#include "MyClientHandler.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h> 
#include <algorithm>
#include <iostream>
#include <deque>
#include <cstring>
using namespace std;
bool hasEnding(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}
//convert a string of X,Y,... (with/without spaces) to a deque of ints
deque<int> getInts(string str) {
	deque<int> costs;
	string line = std::string(str);
	//first delete spaces
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	//then iterate over ','
	while (line.find(',') != string::npos) {
		string num = line.substr(0, line.find(','));
		//messages.push_back(line);
		//cut 'together'
		costs.push_back(stoi(num));
		line = line.substr(line.find(',') + 1, string::npos);
	}
	//insert last item
	costs.push_back(stoi(line));
	return costs;

}
int MyClientHandler::handleClient(int socket) {
	//read line line until end, save every line
	//the last two lines are start and goal, put then in searchable
	//build the matrix from all of the other lines
	//vector<string> messages;
	//concat all of the strings
	string together;
	char buffer[1024];
	//read the data, it may be not line by line
	while (!hasEnding(std::string(buffer), "end\n")) {
		for(int i=0;i<1024;i++)
			buffer[i] = 0;
		int valread = read(socket, buffer, 1024);
		//delete the \n
		string line = std::string(buffer);
		//add to the string
		if (!hasEnding(std::string(buffer), "end\n")) {
			//messages.push_back(line);
			together = together + line;
		}
	}
	string temphashed = together;
	//check if solution exists
	if (this->cm->hasSolution(together)){
		std::string str = this->cm->getSolution(together);
		send(socket, str.c_str(), strlen(str.c_str()), 0);
		//cout << "used solution found" << endl;
		return 1;
	}
	vector<string> messages;
	//now we need to get each line, and the last 2 will be the inittial and goal
	//split on together with \n
	while (together.find('\n') != string::npos) {
		string line = together.substr(0, together.find('\n'));
		messages.push_back(line);
		//cut 'together'
		together = together.substr(together.find('\n') + 1, string::npos);
	}
	//if there's something left, insert it
	if(together.length()>0)
		messages.push_back(together);
	for (auto it = messages.begin(); it != messages.end(); it++) {
		//cout << *it << endl;
		//cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	}
	//now we have every line, including entry and exit
	string goal = messages.back();
	messages.pop_back();
	std::pair<int, int> goalPair(stoi(goal.substr(0, goal.find(","))), stoi(goal.substr(goal.find(",")+1)));
	string initial= messages.back();
	messages.pop_back();
	std::pair<int, int> initialPair(stoi(initial.substr(0, initial.find(","))), stoi(initial.substr(initial.find(",") + 1)));
	deque<deque<int>> costsLines;
	//now interpet these into tuples
	for (auto it = messages.begin(); it != messages.end(); it++) {
		//vector<int> costsLine;
		string line = *it;
		deque<int> ints = getInts(line);
		//helper method
		costsLines.push_back(ints);
		for (auto it2 = ints.begin(); it2 != ints.end(); it2++) {
		}

	}
	//create the problem
	MatrixProblem mp(costsLines,initialPair,goalPair);
	//use the solver to solve it and return a solution
	vector<State<std::pair<int, int>>*> sol=this->solver->solve(mp);
	//reverse the vector, it's from end to start
	std::reverse(sol.begin(), sol.end());
	deque< string> actions;
	deque<int> costsVec;
	//convert the start-to end vector to the printable string
	for (auto it = sol.begin(); it+1 != sol.end(); it++) {
		 
		int i2 = (*it)->getState().first;
		int j2 = (*it)->getState().second;
		State<std::pair<int, int>>* son = *(it+1);
		pair<int, int> pairFa =son->getState();
		int i = pairFa.first;
		int j = pairFa.second;
		//different cases- how to get from father to son
		if (i2 == i && j2 == j - 1) {
			actions.push_back("Right");
		}
		else if (i2 == i && j2 == j + 1) {
			actions.push_back("Left");
		}
		else if (i2 == i-1 && j2 == j ) {
			actions.push_back("Down");
		}
		else if (i2 == i + 1 && j2 == j) {
			actions.push_back("Up");
		}
		else {

		}
		//insert cost
		costsVec.push_back((son)->getCost());
		
	}
	string msg="";
	//send the solution back to client-construct the string
	while (actions.size() > 0) {
		string action = actions.front();
		actions.pop_front();
		int cost = costsVec.front();
		costsVec.pop_front();
		if (actions.size() != 0) {
			msg += action + " (" + std::to_string(cost) + ") ,";
		}
		else {
			msg += action + " (" + std::to_string(cost) + ")";
		}
	}
	//save the solution to cahceManager
	this->cm->setSolution(temphashed, msg+'\n');
	//send to client
	send(socket, msg.c_str(), strlen(msg.c_str()), 0);
}