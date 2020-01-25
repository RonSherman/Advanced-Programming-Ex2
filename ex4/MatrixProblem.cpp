#include "MatrixProblem.h"
#include "MatrixState.h"
#include "CordinateState.h"
#include <cstdlib>
#include <algorithm>
using namespace std;
//create the matrix from lines of string and initial and goal states
MatrixProblem::MatrixProblem(std::deque<std::deque<int>> lines, pair<int,int> initial, pair<int,int> goal ) {
	
	this->initial = new CordinateState(initial);
	this->goal = new CordinateState(goal);
	//convert the vector of vectors to int**
	this->dimColumns=lines.front().size();
	this->dimRows = lines.size();
	//this is the whole matrix pointers
	//int** matrix = new int*[this->dimRows];
	int **matrix = new int*[this->dimRows];

	//int** matrix= (int**)malloc(this->dimRows * sizeof(int*));
	State<std::pair<int, int>>*** states = new State<std::pair<int, int>>**[this->dimRows];
	//allocate each row and add it to the matrix
	//for (int i = 0; i < this->dimRows; i++) {
		//int* row = (int*)malloc(this->dimColumns * sizeof(int));
		//matrix[i] = row;
	//}
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
		}
	}
	//initilize states with values
	for (int i = 0; i < this->dimRows; ++i) {
		int col = this->dimColumns;
		states[i] = new State<std::pair<int, int>>*[col];
		//initailize the row
		for (int j = 0; j < col; j++) {
			states[i][j]  = new CordinateState(pair<int, int>(i, j));
		}
	}
	//assign them to fields
	this->MovingCosts = matrix;
	this->states = states;

}
//TODO
std::vector<State<std::pair<int, int>>*> MatrixProblem::getAllNeighbors(State<std::pair<int, int>>* state) {
	//need to divide based on where the state is located
	int i = state->getState().first;
	int j= state->getState().second;
	vector<State<std::pair<int, int>>*> neighbors;
	//if it's near the bottom line
	/*if (i == this->dimRows - 1) {

	}
	//if it's in the top row
	else if (i == 0) {

	}
	else if(j==0)*/
	//iterate over neighbors
	for (int ii = std::max(i - 1, 0); ii <= min(i + 1, this->dimRows - 1); ii++) {
		for (int jj = max(j - 1, 0); jj <= min(j + 1, this->dimColumns - 1); jj++) {
			State<std::pair<int, int>>* neighborState= this->states[ii][jj];
			//get rid of walls
			if (neighborState->getCost() != -1) {
				neighbors.push_back(neighborState);
			}
		}
	}
	std::vector<State<std::pair<int, int>>*> vec;
	return vec;
}
int MatrixProblem::getMovingCost(State<std::pair<int, int>>* state) {
	int i = state->getState().first;
	int j = state->getState().second;
	return this->MovingCosts[i][j];
}