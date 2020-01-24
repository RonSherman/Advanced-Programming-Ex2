#include "MyClientHandler.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h> 
#include <algorithm>
using namespace std;
bool hasEnding(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}
vector<int> getInts(string str) {
	vector<int> costs;
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
	char buffer[2048];
	//read the data, it may be not line by line
	while (!hasEnding(std::string(buffer), "end\n")) {
		int valread = read(socket, buffer, 1024);
		//delete the \n
		string line = std::string(buffer);
		//std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
		//line.erase(end_pos, line.end());
		//buffer[strlen(buffer) - 1] = '\0';
		//if (line.find('\r') != string::npos)
		//	line = line.substr(0, line.find('\r'));
		//if (line.find('\n') != string::npos)
			//line = line.substr(0, line.find('\n'));
		//add to the vertor
		if (!hasEnding(buffer, "end\n")) {
			//messages.push_back(line);
			together = together + line;
		}
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
	//now we have every line, including entry and exit
	string goal = messages.back();
	messages.pop_back();
	string initial= messages.back();
	messages.pop_back();
	vector<vector<int>> costs;
	//now interpet these into tuples
	for (auto it = messages.begin(); it != messages.end(); it++) {
		//vector<int> costsLine;
		string line = *it;
		//helper method
		costs.push_back(getInts(line));
	}
	//create the problem
	//MatrixProblem mp;
	//use the solver to solve it and return a solution (still need to decide what's it)
	//send the solution back to client
	//this->
}