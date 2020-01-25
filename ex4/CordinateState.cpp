#include "CordinateState.h"
bool CordinateState::equals(State <std::pair<int, int>>* otherState) {
	return this->state.first == otherState->getState().first && this->state.second == otherState->getState().second;
		//&& this->state.second == otherState->state;
};
//returns a vector from the goal to the intial
std::vector<State<std::pair<int, int>>*> CordinateState::backtrack() {
	std::vector<State<std::pair<int, int>>*> vec;
	State<std::pair<int, int>>* it = this;
	while (it != NULL) {
		vec.push_back(it);
		it = it->getFather();
	}
	return vec;
}

/*CordinateState::CordinateState(CordinateState & anotherState) : state(anotherState.g){
	std::pair<int, int> pair(anotherState.getState().first, anotherState.getState().second);
	this->state = pair;
	this->cost = anotherState.getCost();
	//return CordinateState(pair);
}*/
