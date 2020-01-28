#include "MatrixProblem.h"
#include "CordinateState.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
//create the matrix from lines of string and initial and goal states
MatrixProblem::MatrixProblem(std::deque<std::deque<int>> lines, pair<int,int> initial, pair<int,int> goal ) {
	
	this->initial = new CordinateState(initial);
	this->initial->setParent(NULL);
	this->goal = new CordinateState(goal);
	//convert the vector of vectors to int**
	this->dimColumns=lines.front().size();
	this->dimRows = lines.size();
	//this is the whole matrix pointers
	int **matrix = new int*[this->dimRows];
	State<std::pair<int, int>>*** states2 = new State<std::pair<int, int>>**[this->dimRows];
	//allocate each row and add it to the matrix
	for (int i = 0; i < this->dimRows; ++i) {
		matrix[i] = new int[this->dimColumns];
	}
	//initialize matrix with values
	int dimRows = this->dimRows;
	int dimCols = this->dimColumns;
	for (int i = 0; i < dimRows;i++) {

		deque<int> lineOfCosts = lines.front();
		lines.pop_front();
		//assign costs to each slot in row
		for (int j = 0; j < dimCols; j++) {
			int cost_ij = lineOfCosts.front();
			lineOfCosts.pop_front();
			matrix[i][j] = cost_ij;
			//cout << cost_ij << ",";
		}
		//cout << endl;
	}
	this->initial->setCost(matrix[initial.first][initial.second]);
	//initilize states with values
	for (int i = 0; i < this->dimRows; ++i) {
		int col = this->dimColumns;
		states2[i] = new State<std::pair<int, int>>*[col];
		//initailize the row
		for (int j = 0; j < col; j++) {
			CordinateState* asd = new CordinateState(pair<int, int>(i, j));
			asd->setHeuristic(this->getHeuristicFunc(asd));
			//put heuristic val
			states2[i][j] = asd;
		}
	}
	//assign them to fields
	this->MovingCosts = matrix;
	this->states = states2;

}
//TODO
std::vector<State<std::pair<int, int>>*> MatrixProblem::getAllNeighbors(State<std::pair<int, int>>* state) {
	//need to divide based on where the state is located
	int i = state->getState().first;
	int j= state->getState().second;
	//cout << "MatrixProb:searching for neighbors" << i << "," << j << endl;
	vector<State<std::pair<int, int>>*> neighbors;
	//neighbors in same column
	for (int ii = std::max(i - 1, 0); ii <= min(i + 1, this->dimRows - 1); ii++) {
		if (ii == i) continue;
		State<std::pair<int, int>>* neighborState = this->states[ii][j];
		//get rid of walls
		if (this->MovingCosts[ii][j] != -1) {
			neighbors.push_back(neighborState);
		}
	}
	//neighbors in same row
	for (int jj = max(j - 1, 0); jj <= min(j + 1, this->dimColumns - 1); jj++) {
		if (jj == j) continue;
		State<std::pair<int, int>>* neighborState = this->states[i][jj];
		//cout << "got here- neig" << endl;
		//get rid of walls
		if (this->MovingCosts[i][jj] != -1) {
			neighbors.push_back(neighborState);
		}
	}
	return neighbors;
}
int MatrixProblem::getMovingCost(State<std::pair<int, int>>* state) {
	int i = state->getState().first;
	int j = state->getState().second;
	return this->MovingCosts[i][j];
}
/*int MatrixProblem::manhatanDistance(State<std::pair<int, int>>* state) {
	return (abs(state->getState().first - goal->getState().first) +
		abs(state->getState().second - goal->getState().second));
}*/
int MatrixProblem::getHeuristicFunc(State<std::pair<int, int>>* state) {
	//this calculates the manhtann distance
	return (abs(state->getState().first - goal->getState().first) +
		abs(state->getState().second - goal->getState().second));
}