//
// Created by amitnir29 on 25/01/2020.
//

#ifndef MITKADEMEX4_DFS_H
#define MITKADEMEX4_DFS_H

#include <stack>
#include <unordered_set>
#include "Searcher.h"
#include "State.h"
#include <mutex>
#include <bits/unordered_map.h>

template <typename T>
class DFS  : public Searcher<T>  {
    int numNodesEvaluated = 0;
    std::stack<State<T>*> stack;
	std::mutex mutex;
public:
    int getNumOfNodesEvaluated() override { return this->numNodesEvaluated; } ;
    std::vector<State<T>*> search(Searchable<T>* s) override {
		mutex.lock();
        stack.push(s->getInitialState());
		std::unordered_map<std::string, State<T>*> been;
		been.insert({ s->getInitialState()->toString(),s->getInitialState() });


        while (!stack.empty()) {
            State<T>* n = stack.top();
			stack.pop();
            numNodesEvaluated++;
            if (n->equals(s->getGoalState())) {
				//cout << "FOUND GOAL" << endl;
				//cout << "DFS EVALUATED:" << numNodesEvaluated << endl;
				mutex.unlock();
                return n->backtrack();
            }

            std::vector<State<T>*> neighbors = s->getAllNeighbors(n);
            auto it = neighbors.begin();
            //for each neighbor
            for (; it != neighbors.end(); it++) {
                //need to get moving cost on 'it' somehow
                int currCost = n->getCost() + s->getMovingCost(n);

                //if isn't in closed and isn't in open
                if (been.find((*it)->toString()) == been.end()) {
					been.insert({ (*it)->toString(),*it });

                    //this isn't done by searchable
                    (*it)->setParent(n);
                    (*it)->setCost(currCost);

                    stack.push(*it);

                }

            }
        }
    };


};


#endif //MITKADEMEX4_DFS_H
