#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H
#include "interfaces.h"
#include "SolverSearcher.h"
#include "MatrixProblem.h"
#include "FileCacheManager.h"
class MyClientHandler : public client_handler::ClientHandler{
private:
	//problem,solution, t of state
	//solution= list of states
	//problem=matrix problem
	//state= tuple of x,y
	//TODO- how to represent the solution
	SolverSearcher<MatrixProblem,vector<State<std::pair<int, int>>*>,std::pair<int,int>>* solver;
	FileCacheManager* cm;
public:
	int handleClient(int socket) override;
	MyClientHandler(SolverSearcher<MatrixProblem,
		vector<State<std::pair<int, int>>*>, std::pair<int, int>>* solver, FileCacheManager* cache)
		: solver(solver), cm(cache) {};
};
#endif