#include "BestSearch.h"

//template<typename T>
//std::vector<State<T>*> BestSearch<T>::search(Searchable<T>* s) {
	////this->;
	//std::unordered_set<State<T>*> closed;
	//while (this->openList.length()>0) {
	//	State<T>* n = this->openList.pop();
	//	closed.insert(n);
	//	if (n->equals(s->getGoalState())) {
	//		//return backtrace
	//		return n->backtrack();
	//	}
	//	std::vector<State<T>*> neighbors = s->getAllNeighbors(n);
	//	auto it= neighbors.begin();
	//	//for each neighbor
	//	for (; it != neighbors.end(); it++) {
	//		//if isn't in closed and isn't in open
	//		if (closed.find(*it) == closed.end() && !this->openList.contains(*it)) {
	//			//it.setParent(n)
	//			this->openList.insert(*it);
	//		}
	//		else {
	//			//if not in open,add to open
	//			//if (!this->openList.contains(*it)) {
	//			//	this->openList.insert(*it);
	//			//}
	//			//if in closed, continue loop
	//			if (closed.find(*it) != closed.end()) {
	//				continue;
	//			}
	//			//else, the node isn't in closed and is in open
	//			else {
	//				//remove the old value
	//				//this->openList.remove(*it);
	//				//insert the node with the new value
	//				//this->openList.insert(*it);
	//				this->openList.decrease_key(*it);
	//			}
	//		}
	//	}
	//}
//}