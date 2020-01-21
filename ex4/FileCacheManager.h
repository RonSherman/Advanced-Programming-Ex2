//
// Created by amitnir29 on 17/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "interfaces.h"
#include <string>
using namespace problem_solving;

template<typename Solution>
class FileCacheManager : public CacheManager<std::string, Solution> {
public:
	bool hasSolution(std::string s) override { return false; };

	Solution getSolution(std::string p) override {
		return Solution();
	};

	int setSolution(std::string p, Solution sol) override {
		return 0;
	};
};


#endif //EX4_FILECACHEMANAGER_H
