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
        //auto compare=[](State<T>* lhs, State<T>* rhs) {
        //	return lhs->getCost() > rhs->getCost();
        //};

        //this->openList.setQueue(cmp);

        //this->;
        /*struct myClassComp {
            bool operator() (const State<T>* lhs, const State<T>* rhs) const
            {
                return *lhs < *rhs;
            }
        };*/
        //std::unordered_set<State<T>*, myClassComp> closed;
        this->openList.insert(s->getInitialState());
        //std::unordered_set< State<T>*> closed;
        std::unordered_map< string, State<T>*> closed;
        while (this->openList.length() > 0) {
            //cout << "executed loop:BestSearch" << endl;
            State<T>* n = this->openList.pop();
            this->numNodesEvaluated++;
            if (closed.find(n->toString()) == closed.end()) {
                closed.insert({ n->toString(),n });
            }
            //cout << "inserted "<<n->getCost()<< "to closed list-size" <<closed.size()<< endl;

            if (n->equals(s->getGoalState())) {
                cout << "FOUND GOAL" << endl;
                cout << "ASTAR EVALUATED:" << numNodesEvaluated << endl;
				mutex.unlock();
                //return backtrace
                return n->backtrack();
            }
            std::vector<State<T>*> neighbors = s->getAllNeighbors(n);
            auto it = neighbors.begin();
            if (neighbors.size() == 0) {
                cout << "NO NEIGHBORS" << endl;
            }
            //int currCost = n->getCost() + s->getMovingCost(n);

            //for each neighbor
            for (; it != neighbors.end(); it++) {
                int currCost = n->getCost() + s->getMovingCost((*it));
                //<<(CordinateState)(*(*it))
                //cout << "for each neighbor- "  <<endl;
                //cout << "current cost:" << currCost << endl;
                //if it's unreachable
                //if ((*it)->getCost() == -1)
                //	continue;
                //need to get moving cost on 'it' somehow

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
                        //cout << "not in closed and is in open" << endl;
                        //this->openList.remove(*it);
                        //insert the node with the new value
                        //this->openList.insert(*it);
                        //this->openList.decrease_key(*it);
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


#endif //MITKADEMEX4_ASTAR_H
