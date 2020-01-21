//
// Created by amitnir29 on 17/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "interfaces.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//template<typename Solution>
class FileCacheManager : public problem_solving::CacheManager<string, string> {
	int capacity = 0;
	//hold list of hashed string problems, to check if we have a file for it
	unordered_set <string> set;
	//list <string> names;
	//unordered_map <string, pair <T, list <string>::iterator>> map;
public:
	bool hasSolution(string s) override ;

	std::string getSolution(string p) override;

	void setSolution(std::string p, string sol) override;
};


#endif //EX4_FILECACHEMANAGER_H
