//
// Created by amitnir29 on 25/01/2020.
//

#ifndef MITKADEMEX4_BFS_H
#define MITKADEMEX4_BFS_H

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "Searcher.h"
#include "State.h"

template <typename T>
class BFS  : public Searcher<T>  {
    int numNodesEvaluated = 0;
    std::queue<State<T>*> queue;

public:
    int getNumOfNodesEvaluated() override { return this->numNodesEvaluated; } ;
	std::vector<State<T>*> search(Searchable<T>* s) override {
		queue.push(s->getInitialState());
		std::unordered_map<std::string, State<T>*> been;
		been.insert({ s->getInitialState()->toString(),s->getInitialState()});
		//{ n->toString(), n }

        while (!queue.empty()) {
			State<T>* n = queue.front();
			queue.pop();
            numNodesEvaluated++;
            if (n->equals(s->getGoalState())) {
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

                    queue.push(*it);

                }

            }
        }
    };


};


#endif //MITKADEMEX4_BFS_H
