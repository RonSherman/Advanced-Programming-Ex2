#ifndef FLIGHTSIMULATOR_BESTSEARCH_H
#define FLIGHTSIMULATOR_BESTSEARCH_H
#include "Searcher.h"
#include "MyPriorityQueue.h"
#include "Searchable.h"
#include "State.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include "CordinateState.h"
#include <unordered_map>
#include "AStarComparator.h"
#include <mutex>
using namespace std;
template <typename T>
class BestSearch : public Searcher<T> {
private:
	int numNodesEvaluated = 0;
	MyPriorityQueue<T, StateComparator<T>> openList;
	std::mutex mutex;
	//std::pri
	//priority queue openList
	//set ClosedList
public:
	static bool cmp(State<T>* lhs, State<T>* rhs) {
		return lhs->getCost() > rhs->getCost();
	};
	int getNumOfNodesEvaluated() override { return this->numNodesEvaluated; } ;
	std::vector<State<T>*> search(Searchable<T>* s) override {
		mutex.lock();
		this->numNodesEvaluated = 0;
		this->openList.insert(s->getInitialState());
		//std::unordered_set< State<T>*> closed;
		std::unordered_map< string, State<T>*> closed;
		while (this->openList.length() > 0) {
			State<T>* n = this->openList.pop();
			this->numNodesEvaluated++;
			if (closed.find(n->toString()) == closed.end()) {
				closed.insert({ n->toString(),n });
			}

			if (n->equals(s->getGoalState())) {
				//cout << "FOUND GOAL" << endl;
				//cout << "BEST EVALUATED:" << numNodesEvaluated << endl;
				mutex.unlock();
				//return backtrace
				return n->backtrack();
			}
			std::vector<State<T>*> neighbors = s->getAllNeighbors(n);
			auto it = neighbors.begin();
			
			//for each neighbor
			for (; it != neighbors.end(); it++) {
				int currCost = n->getCost() + s->getMovingCost((*it));
				
				//if isn't in closed and isn't in open
				if (closed.find((*it)->toString()) == closed.end() && !this->openList.contains(*it)) {
					//cout << "not in both" << endl;
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
					if (closed.find((*it)->toString()) != closed.end()) {
						//cout << "found in closed" << endl;
						continue;
					}
					//else, the node isn't in closed and is in open
					else {
						//if it's lower tham before, remove the old value
						if ((*it)->getCost()>currCost) {
							//cout << "updated new cost" << endl;
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