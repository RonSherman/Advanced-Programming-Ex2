#ifndef EX4_CORDINATESTATE_H
#define EX4_CORDINATESTATE_H
#include "State.h"
#include <utility>
class CordinateState : public State<std::pair<int,int>> {
public:
	bool equals(State <std::pair<int, int>>* otherState) override;
	std::vector<State<std::pair<int, int>>*> backtrack() override ;
	CordinateState(std::pair<int, int> st) : State(st) { this->cost = 0; };
	CordinateState(CordinateState& anotherState);
	//CordinateState() {};
};
#endif