#include "interfaces.h"
#include "SolverSearcher.h"
#include "MatrixProblem.h"
class MyClientHandler : public client_handler::ClientHandler{
private:
	//problem,solution, t of state
	//solution= list of states
	//problem=matrix problem
	//state= tuple of x,y
	//TODO- how to represent the solution
	SolverSearcher<MatrixProblem,std::pair<int,int>> solver;
public:
	int handleClient(int socket) override;
	MyClientHandler(SolverSearcher<MatrixProblem, std::pair<int, int>> solver) : solver(solver) {};
};