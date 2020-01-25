#ifndef FLIGHTSIMULATOR_BESTSEARCH_H
#define FLIGHTSIMULATOR_BESTSEARCH_H
#include "Searcher.h"
#include "MyPriorityQueue.h"
#include "Searchable.h"
#include "State.h"
#include <unordered_set>
#include <vector>
template <typename T>
class BestSearch : public Searcher<T> {
private:
	int numNodesEvaluated = 0;
	MyPriorityQueue<T> openList;
	//std::pri
	//priority queue openList
	//set ClosedList
public:
	int getNumOfNodesEvaluated() override { return this->numNodesEvaluated; } ;
	std::vector<State<T>*> search(Searchable<T>* s) override {
		//this->;
		std::unordered_set<State<T>*> closed;
		while (this->openList.length() > 0) {
			State<T>* n = this->openList.pop();
			closed.insert(n);
			if (n->equals(s->getGoalState())) {
				//return backtrace
				return n->backtrack();
			}
			std::vector<State<T>*> neighbors = s->getAllNeighbors(n);
			auto it = neighbors.begin();
			//for each neighbor
			for (; it != neighbors.end(); it++) {
				//if it's unreachable
				//if ((*it)->getCost() == -1)
				//	continue;
				//need to get moving cost on 'it' somehow
				int currCost = n->getCost() + s->getMovingCost(n);
				//if isn't in closed and isn't in open
				if (closed.find(*it) == closed.end() && !this->openList.contains(*it)) {
					//this isn't done by searchable
					(*it)->setParent(n);
					(*it)->setCost(currCost);
					this->openList.insert(*it);
				}
				else {
					//if not in open,add to open
					//if (!this->openList.contains(*it)) {
					//	this->openList.insert(*it);
					//}
					//if in closed, continue loop
					if (closed.find(*it) != closed.end()) {
						continue;
					}
					//else, the node isn't in closed and is in open
					else {
						
						//this->openList.remove(*it);
						//insert the node with the new value
						//this->openList.insert(*it);
						//this->openList.decrease_key(*it);
						//if it's lower tham before, remove the old value
						if ((*it)->getCost()>currCost) {
							(*it)->setParent(n);
							(*it)->setCost(currCost);
							this->openList.decrease_key(*it);
						}
					}
				}
			}
		}
	};
};
#endif