#include "MyPriorityQueue.h"
#include <vector>
template <typename T>
State<T>* MyPriorityQueue<T>::pop() {
	State<T>* sta =this->queue.top();
	this->queue.pop();
	//remove from the set
	this->set.erase(sta);
	return sta;
}
template <typename T>
int MyPriorityQueue<T>::length() {
	return this->queue.size();
}
template <typename T>
bool MyPriorityQueue<T>::contains(State<T>* state){
	//use the set to check contains as its faster, and non existent in priority queue
	return this->set.find(state) != this->set.end();
}
template <typename T>
void MyPriorityQueue<T>::insert(State<T>* state) {
	//ad to queue and set
	this->queue.push(state);
	this->set.insert(state);
}
template <typename T>
void MyPriorityQueue<T>::decrease_key(State<T>* state){
	//remove from queue and set
	//this->set.erase(state);
	//we will change the value, pop everyone out and insert back in
	//*state->cost = newCost;
	//temporary for holding the objects
	std::vector<State<T>*> temp;
	while (this->queue.size() > 0) {
		temp.push_back(this->queue.top());
		this->queue.pop();
	}
	//insert everything back in, now it will be sorted, with the new value in place
	while (temp.size() > 0) {
		State<T>* sa=temp.pop_back();
		this->queue.push(sa);
	}
	//removing from queue is harder- set to minus infinity and pop
	//int minus_inf=std::numeric_limits<int>::min();
	//s
}