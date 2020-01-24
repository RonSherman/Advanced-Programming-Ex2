#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H
#include "interfaces.h"
#include <string>
class StringReverser : public  problem_solving::Solver<std::string, std::string>{
	std::string solve(std::string s) override;
};
#endif
