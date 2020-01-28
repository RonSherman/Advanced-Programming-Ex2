#ifndef EX4_MYPRIORITYQUEUE_H
#define EX4_MYPRIORITYQUEUE_H
#include <queue>
#include "State.h"
#include "StateComparator.h"
#include <unordered_set>
#include <iostream>
#include <functional>
#include <unordered_map>
using namespace std;
template <typename T,typename Comparator>
class MyPriorityQueue {
private:
	//the actual priority queue
	std::priority_queue<State<T>*,std::vector<State<T>*>,Comparator> queue;
	//to check if item in the queue, a map of all the items in queue
	std::unordered_map<string, State<T>*> map;
public:
	void setQueue(const function<bool(State<T>* , State<T>*)> func) {
		std::priority_queue<State<T>*, std::vector<State<T>*>, decltype(func)> temp(func);
		this->queue= temp;
	}
	//void remove(State<T>* state);
	void decrease_key(State<T>* state){
	//remove from queue and set
	//we will change the value, pop everyone out and insert back in as STL doesnt support it natively

	//temporary for holding the objects
		std::vector<State<T>*> temp;
		while (this->queue.size() > 0) {
			temp.push_back(this->queue.top());
			this->queue.pop();
		}
		//insert everything back in, now it will be sorted, with the new value in place
		while (temp.size() > 0) {
			State<T>* sa = temp.back();
			temp.pop_back();
			this->queue.push(sa);
		}
	};
	State<T>* pop() {
		State<T>* sta = this->queue.top();
		this->queue.pop();
		//remove from the set also
		//this->set.erase(sta);
		this->map.erase(sta->toString());
		return sta;
	};
	void insert(State<T>* state) {
		//add to queue and set
		this->queue.push(state);
		this->map.insert({ state->toString(),state });

	};
	int length() {
		return this->queue.size();
	};
	bool contains(State<T>* state) {
		//use the set to check contains as its faster, and non existent in priority queue
		return this->map.find(state->toString()) != this->map.end();
	};
};
#endif