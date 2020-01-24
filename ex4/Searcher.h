#ifndef FLIGHTSIMULATOR_SEARCH_H
#define FLIGHTSIMULATOR_SEARCH_H
#include "Searchable.h"
template <typename Solution,typename T>
class Searcher {
	Solution search(Searchable<T> s)=0;
	int getNumOfNodesEvaluated()=0;
};
#endif