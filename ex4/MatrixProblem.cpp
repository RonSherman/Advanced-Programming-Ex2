#include "MatrixProblem.h"
#include "MatrixState.h"
#include "CordinateState.h"
#include <cstdlib>
using namespace std;
//create the matrix from lines of string and initial and goal states
MatrixProblem::MatrixProblem(std::vector<std::vector<int>> lines, pair<int,int> initial, pair<int,int> goal ) {
	
	this->initial = new CordinateState(initial);
	this->goal = new CordinateState(goal);
	//convert the vector of vectors to int**
	this->dimColumns=lines.front().size();
	this->dimRows = lines.size();
	//this is the whole matrix pointers
	int** matrix= (int**)malloc(this->dimRows * sizeof(int*));

	//allocate each row and add it to the matrix
	for (int i = 0; i < this->dimRows; i++) {
		int* row = (int*)malloc(this->dimColumns * sizeof(int));
		matrix[i] = row;
	}
}
//TODO
std::vector<State<std::pair<int, int>>*> MatrixProblem::getAllNeighbors(State<std::pair<int, int>>* state) {
	//need to divide based on where the state is located
	int i = state->getState()->first;
	int j= state->getState()->second;
	std::vector<State<std::pair<int, int>>*> vec;
	return vec;
}