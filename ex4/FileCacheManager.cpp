//
// Created by amitnir29 on 17/01/2020.
//

#include "FileCacheManager.h"
#include <fstream>
#include <iostream>
void FileCacheManager::setSolution(std::string p, std::string sol) {
	//set map as key=p and val=sol
	//create the file
	//this->map[p] = sol;
	//hash the values of p
	hash<string> hasher;
	size_t hash = hasher(p);
	string fileName = to_string(hash);
	this->set.insert(fileName);
	//cout << "created " + p + " with hash:" + fileName << endl;
	//truncate the last file
	ofstream ofile(fileName + ".txt",std::ios::trunc);
	if (ofile) {
		ofile << sol;
		ofile.close();
	}
}
bool FileCacheManager::hasSolution(std::string p) {
	//check if map contains p as key
	//return that
	hash<string> hasher;
	size_t hash = hasher(p);
	string fileName = to_string(hash);
	//return this->set.find(fileName) != set.end();
	//check if a file exists
	fstream f(fileName + ".txt");
	if (f.is_open()) {
		f.close();
		return true;
	}
	return false;
}
std::string FileCacheManager::getSolution(std::string p) {
	//read the file with map.get(p) name and return what's inside
	//string fileName = this->map.find(p)->second;
	hash<string> hasher;
	size_t hash = hasher(p);
	string fileName = to_string(hash);
	//text reading
	ifstream ifile(fileName+".txt");
	//if file got opened
	if (ifile) {
		string total;
		string sol;
		//ifile >> sol;
		while (getline(ifile, sol)){
			//cout << sol << endl;
			total += sol;
			//cout << line << '\n';
		}
		//cout << "got " + total << endl;
		ifile.close();
		return total;
	}
	else {
		cout << "FAILED: getSolution opening file" << endl;
		exit(1);
	}

}
/*template <class Solution>
bool FileCacheManager<Solution>::hasSolution(std::string s) {
    return false;
}
template <class Solution>
Solution FileCacheManager<Solution>::getSolution(std::string s) {
    return Solution();
}
template <class Solution>
int FileCacheManager<Solution>::setSolution(std::string s, Solution sol) {
    return 0;
}*/
