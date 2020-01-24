#ifndef FLIGHTSIMULATOR_BESTSEARCH_H
#define FLIGHTSIMULATOR_BESTSEARCH_H
#include "Searcher.h"
#include "MyPriorityQueue.h"
template <typename Solution,typename T>
class BestSearch : public Searcher<Solution,T> {
private:
	int numNodesEvaluated = 0;
	MyPriorityQueue<T> openList;
	//std::pri
	//priority queue openList
	//set ClosedList
public:
	int getNumOfNodesEvaluated() { return this->numNodesEvaluated; };
	Solution search(Searchable<T> s);
};
#endif