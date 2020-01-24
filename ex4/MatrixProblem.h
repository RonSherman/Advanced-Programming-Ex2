#include "Searchable.h"
#include "CordinateState.h"
#include <vector>
using namespace std;
class MatrixProblem : public Searchable<std::pair<int,int>>{
private:
	int dim;
	//we need a double array, for each x and y
	int** costs;
	State<std::pair<int, int>>*** states;
public:
	MatrixProblem(vector<vector<int>> lines, std::pair<int, int> initial, std::pair<int, int> goal);
	State<std::pair<int, int>>* getInitialState() override { return this->initial; };
	State<std::pair<int, int>>* getGoalState() override { return this->goal; };
	//List<State<T>> getAllNeighbors(State<T> state)=0;
	std::vector<State<std::pair<int, int>>*> getAllNeighbors(State<std::pair<int, int>>* state) override ;

};