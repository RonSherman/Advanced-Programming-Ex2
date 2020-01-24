#include <queue>
#include "State.h"
#include "StateComparator.h"
#include <unordered_set>
template <typename T>
class MyPriorityQueue {
private:
	//the actual priority queue
	std::priority_queue<State<T>*,std::vector<State<T>*>,StateComparator<T>> queue;
	//to check if item in the queue, a set of all the items in queue
	std::unordered_set < State<T>*> set;
public:
	//void remove(State<T>* state);
	void decrease_key(State<T>* state);
	State<T>* pop();
	void insert(State<T>* state);
	int length();
	bool contains(State<T>* state);
};