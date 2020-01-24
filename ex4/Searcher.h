#ifndef FLIGHTSIMULATOR_SEARCH_H
#define FLIGHTSIMULATOR_SEARCH_H
#include "Searchable.h"
#include <vector>
template <typename T>
class Searcher {
public:
	virtual std::vector<State<T>*> search(Searchable<T>* s)=0;
	virtual int getNumOfNodesEvaluated()=0;
};
#endif