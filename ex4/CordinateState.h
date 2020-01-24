#include "State.h"
#include <utility>
class CordinateState : public State<std::pair<int,int>> {
	bool equals(State <std::pair<int, int>>* otherState) override;
};