#include "State.h"
//just add functionality of up,down etc. Interface segregation- not every state moves this way
template<typename T>
class MatrixState : public State<T> {
private:
	Action actionToHere;
public:
	enum class Action {Up,Left,Right,Down};
};