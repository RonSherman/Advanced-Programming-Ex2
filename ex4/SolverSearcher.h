#ifndef EX4_SOLVERSEARCHER_H
#define EX4_SOLVERSEARCHER_H
#include "interfaces.h"
#include "Searcher.h"
template <typename Problem, class Solution,typename T>
class SolverSearcher : public problem_solving::Solver<Problem,Solution> {
private:
	Searcher<T>* searcher;
public:
	SolverSearcher(Searcher<T>* s) : searcher(s) {};
	Solution solve(Problem p) { return this->searcher->search(&p); };
};
#endif