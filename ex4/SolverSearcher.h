#include "interfaces.h"
#include "Searcher.h"
template <typename Problem, class Solution,typename T>
class SolverSearcher : public problem_solving::Solver<Problem,Solution> {
private:
	Searcher<Solution,T> searcher;
public:
	SolverSearcher(Searcher<Solution,T> s) : searcher(s) {};
	Solution solve(Problem p) { this->searcher.search(p); };
};