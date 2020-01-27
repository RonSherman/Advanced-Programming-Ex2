#ifndef EX4_MYPRIORITYQUEUE_H
#define EX4_MYPRIORITYQUEUE_H
#include <queue>
#include "State.h"
#include "StateComparator.h"
#include <unordered_set>
#include <iostream>
#include <functional>
using namespace std;
template <typename T>
class MyPriorityQueue {
private:
	//the actual priority queue
	std::priority_queue<State<T>*,std::vector<State<T>*>,StateComparator<T>> queue;
	//to check if item in the queue, a set of all the items in queue
	std::unordered_set < State<T>*> set;
public:
	//MyPriorityQueue(std::priority_queue newQueue) {
		//this->queue = newQueue;

	//}
	void setQueue(const function<bool(T* , T*)> func) {
		std::priority_queue<State<T>*, std::vector<State<T>*>, decltype(func)> temp(func);
		this->queue= temp;
	}
	//void remove(State<T>* state);
	void decrease_key(State<T>* state){
		//remove from queue and set
	//this->set.erase(state);
	//*state->cost = newCost;
	//we will change the value, pop everyone out and insert back in

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
		//removing from queue is harder- set to minus infinity and pop
		//int minus_inf=std::numeric_limits<int>::min();
		//s
	};
	State<T>* pop() {
		State<T>* sta = this->queue.top();
		this->queue.pop();
		//remove from the set also
		this->set.erase(sta);
		return sta;
	};
	void insert(State<T>* state) {
		//add to queue and set
		this->queue.push(state);
		this->set.insert(state);
		cout << "After insersion queue size is- " << this->queue.size() << endl;
		//cout << "After insersion set size is- " << this->set.size() << endl;

	};
	int length() {
		return this->queue.size();
	};
	bool contains(State<T>* state) {
		//use the set to check contains as its faster, and non existent in priority queue
		return this->set.find(state) != this->set.end();
	};
};
#endif