#include "tape.h"
#include "state.h"
#include "command.h"
#include "parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	// build a program
	// read a tape
	// install firts position of head
	// program cycle

	if (argc < 2) return 0;
	std::ifstream file(argv[1]);


	Turing::Tape tape('_', 3);
	tape.load('b').load('b').load('c').load('b').load('c').load('b').load('a');

	Turing::Tape::Head head(tape.setHead(-10, Turing::State(0)));
	Turing::Parser parser;
	Turing::Program program(parser.parse(&file));

	Turing::Command cmd;
	std::cout << head << std::endl;

	do {
		cmd = program.command( head.state(), head.observable() );
		std::cout <<
			head.execute( cmd )
		<< std::endl;
	}
	while (cmd != Turing::Command::STOP);
	
	return 0;
}