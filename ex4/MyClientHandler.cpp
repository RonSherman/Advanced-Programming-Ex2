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
	//while(true){

		for(int i=0;i<1024;i++)
			buffer[i] = 0;
		//buffer = { 0 };
		int valread = read(socket, buffer, 1024);
		//delete the \n
		string line = std::string(buffer);
		//cout << "got from client- " << buffer << endl;
		//cout << "===============================" << endl;
		//std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
		//line.erase(end_pos, line.end());
		//buffer[strlen(buffer) - 1] = '\0';
		//if (line.find('\r') != string::npos)
		//	line = line.substr(0, line.find('\r'));
		//if (line.find('\n') != string::npos)
			//line = line.substr(0, line.find('\n'));
		//add to the string
		if (!hasEnding(std::string(buffer), "end\n")) {
			//messages.push_back(line);
			together = together + line;
		}
	}
	//cout << "finished waiting for client" << endl;
	string temphashed = together;
	//cout << together << endl;
	//check if solution exists
	if (this->cm->hasSolution(together)){
		std::string str = this->cm->getSolution(together);
		//cout << "sent to client-" << str << endl;
		//std::string str = Solution::toString();
		//str = str.append("\n");
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
	//cout << together << endl;
	//cout << "got after together" << endl;
	for (auto it = messages.begin(); it != messages.end(); it++) {
		//cout << *it << endl;
		//cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	}
	//cout << "finished messages" << endl;
	//cout << messages.size() << endl;
	//now we have every line, including entry and exit
	string goal = messages.back();
	messages.pop_back();
	std::pair<int, int> goalPair(stoi(goal.substr(0, goal.find(","))), stoi(goal.substr(goal.find(",")+1)));
	//cout << goalPair.first << " "<< goalPair.second<<endl;
	string initial= messages.back();
	messages.pop_back();
	std::pair<int, int> initialPair(stoi(initial.substr(0, initial.find(","))), stoi(initial.substr(initial.find(",") + 1)));
	//cout << initialPair.first << " " << initialPair.second << endl;
	deque<deque<int>> costsLines;
	//now interpet these into tuples
	for (auto it = messages.begin(); it != messages.end(); it++) {
		//vector<int> costsLine;
		string line = *it;
		deque<int> ints = getInts(line);
		//helper method
		costsLines.push_back(ints);
		for (auto it2 = ints.begin(); it2 != ints.end(); it2++) {
			//cout << *it2 <<",";
		}
		//cout << endl<<"END OF LINE"<<endl;

	}
	//cout << "got before matrix" << endl;
	//create the problem
	MatrixProblem mp(costsLines,initialPair,goalPair);
	//cout << "got after matrix" << endl;
	//use the solver to solve it and return a solution (still need to decide what's it)
	vector<State<std::pair<int, int>>*> sol=this->solver->solve(mp);
	//cout << "got after solution" << endl;
	//cout<<this->solver.
	//TODO- equals 0
	//cout <<"Solution size:"<< sol.size() << endl;
	//cout << "Printing solution" << endl;
	for (auto it = sol.begin(); it!= sol.end(); it++) {
		//cout << "("<<(*it)->getState().first << "," << (*it)->getState().second<<")";
	}
	//cout << endl;
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
			//cout << "ACTION NOT FOUND" << endl;

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
	//cout << "SENDING:" << msg << endl;
	//send to client
	send(socket, msg.c_str(), strlen(msg.c_str()), 0);
	//this->
}