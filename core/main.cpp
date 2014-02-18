#include "tape.h"
#include "state.h"
#include "command.h"
#include <iostream>

int main() {
	// build a program
	// read a tape
	// install firts position of head
	// program cycle




	Turing::Tape tape('_', 3);
	tape.load('a').load('b').load('c');
	std::cout << tape << std::endl;
	std::cout << "_________________" << std::endl;

	Turing::Tape::Head head(tape.setHead(-1, Turing::State('a')));
	std::cout << head << std::endl;
	//head.execute(Turing::Command());
	
	//std::cout << tape << std::endl;
	return 0;
}