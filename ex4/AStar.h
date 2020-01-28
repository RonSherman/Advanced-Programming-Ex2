//
// Created by amitnir29 on 26/01/2020.
//

#ifndef MITKADEMEX4_ASTAR_H
#define MITKADEMEX4_ASTAR_H


#include <queue>
#include <unordered_set>
#include "Searcher.h"
#include "State.h"
#include "AStarComparator.h"
#include "MyPriorityQueue.h"
#include <mutex>
template <typename T>
class AStar : public Searcher<T>  {
private:
    int numNodesEvaluated = 0;
    //State<std::pair<int, int>> *goal;
    MyPriorityQueue<T,AStarComparator> openList;
	std::mutex mutex;

public:
    int getNumOfNodesEvaluated() override { return this->numNodesEvaluated; } ;

    std::vector<State<T>*> search(Searchable<T>* s) override {
		mutex.lock();
        //this -> goal = s->getGoalState();
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
				mutex.unlock();
                //return backtrace
                return n->backtrack();
            }
            std::vector<State<T>*> neighbors = s->getAllNeighbors(n);
            auto it = neighbors.begin();
            if (neighbors.size() == 0) {
            }
            //for each neighbor
            for (; it != neighbors.end(); it++) {
                int currCost = n->getCost() + s->getMovingCost((*it));

                //if isn't in closed and isn't in open
                if (closed.find((*it)->toString()) == closed.end() && !this->openList.contains(*it)) {
                    //this isn't done by searchable
                    (*it)->setParent(n);
                    (*it)->setCost(currCost);
                    this->openList.insert(*it);
                }
                else {
                    //if in closed, continue loop
                    if (closed.find((*it)->toString()) != closed.end()) {
                        continue;
                    }
                        //else, the node isn't in closed and is in open
                    else {
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


#endif //MITKADEMEX4_ASTAR_H
