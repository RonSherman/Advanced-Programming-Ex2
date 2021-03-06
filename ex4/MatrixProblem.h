#ifndef EX4_MATRIXPROBLEM_H
#define EX4_MATRIXPROBLEM_H
#include "Searchable.h"
#include "CordinateState.h"
#include <vector>
#include <deque>
using namespace std;
class MatrixProblem : public Searchable<std::pair<int,int>>{
private:
	int dimRows;
	int dimColumns;
	//we need a double array, for each x and y
	int** MovingCosts;
	State<std::pair<int, int>>*** states;
public:
	MatrixProblem(deque<deque<int>> lines, std::pair<int, int> initial, std::pair<int, int> goal);
	State<std::pair<int, int>>* getInitialState() override { return this->initial; };
	State<std::pair<int, int>>* getGoalState() override { return this->goal; };
	//List<State<T>> getAllNeighbors(State<T> state)=0;
	std::vector<State<std::pair<int, int>>*> getAllNeighbors(State<std::pair<int, int>>* state) override ;
	int getMovingCost(State<std::pair<int, int>>*) override;
	//int MatrixProblem::manhatanDistance(State<std::pair<int, int>>* state);
	int  getHeuristicFunc(State<std::pair<int, int>>* state) override;

};
#endif