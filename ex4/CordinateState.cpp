#include "CordinateState.h"
bool CordinateState::equals(State <std::pair<int, int>>* otherState) {
	return this->state.first == otherState->getState()->first && this->state.second == otherState->getState()->second;
		//&& this->state.second == otherState->state;
};