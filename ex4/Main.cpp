#include "interfaces.h"
#include <string>
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "BestSearch.h"
#include "MyPriorityQueue.h"
#include "BFS.h"
#include "DFS.h"
#include <iostream>
#include <vector>
#include "AStar.h"
#include "MyParallelServer.h"
int main(int argc, char* argv[]) {
	
	//part B
	/*problem_solving::Solver< std::string, std::string>* sol = new StringReverser();
	FileCacheManager* cm = new FileCacheManager();
	MyTestClientHandler* handler = new MyTestClientHandler(sol, cm);
	server_side::Server* server = new MySerialServer();*/
	//Part C
	server_side::Server* server = new MyParallelServer();
	DFS<pair<int,int>>* searcher = new DFS<pair<int, int>>();
	//BestSearch<pair<int, int>>* searcher = new BestSearch<pair<int, int>>();
	//using namespace std;
	SolverSearcher<MatrixProblem,vector<State<pair<int, int>>*> ,pair<int, int>>* adapter =
		new SolverSearcher<MatrixProblem, vector<State<pair<int, int>>*>, pair<int, int>>(searcher);
	//TOOD- cache isn't actually doing anything right now
	FileCacheManager* cm = new FileCacheManager();
	MyClientHandler* handler = new MyClientHandler(adapter,cm);
	
	cout << "started server" << endl;
	if(argc>=2)
		server->open(atoi(argv[1]), handler);
	else
		server->open(5600, handler);
	//5State<int> state;
	//MyPriorityQueue<int> queue();
	//server->open(5600, handle);

	return 0;
}