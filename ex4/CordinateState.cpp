#include "CordinateState.h"
#include <iostream>
using namespace std;
bool CordinateState::equals(State <std::pair<int, int>>* otherState) {
	return this->state.first == otherState->getState().first && this->state.second == otherState->getState().second;
		//&& this->state.second == otherState->state;
};
//returns a vector from the goal to the intial
std::vector<State<std::pair<int, int>>*> CordinateState::backtrack() {
	int i = 1;
	std::vector<State<std::pair<int, int>>*> vec;
	State<std::pair<int, int>>* it = this;
	while (it != NULL) {
		cout << "getting father " << i<< endl;
		vec.push_back(it);
		it = it->getFather();
		i++;
	}
	cout << "finished findind dad" << endl;
	return vec;
}
using namespace std;
ostream& operator<<(ostream& os, CordinateState& dt)
{
	os << "(" << dt.getState().first << "," << dt.getState().second << ")";
	return os;
}

/*CordinateState::CordinateState(CordinateState & anotherState) : state(anotherState.g){
	std::pair<int, int> pair(anotherState.getState().first, anotherState.getState().second);
	this->state = pair;
	this->cost = anotherState.getCost();
	//return CordinateState(pair);
}*/
