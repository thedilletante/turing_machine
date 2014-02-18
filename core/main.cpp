#include "tape.h"
#include "state.h"
#include "command.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char *argv[]) {
	// build a program
	// read a tape
	// install firts position of head
	// program cycle

	if (argc < 3) return 0;
	std::ifstream file(argv[1]);


	Turing::Tape tape('_', 3);
	for (size_t i = 0, end = strlen(argv[2]); i < end; ++i)
		tape.load(argv[2][i]);

	Turing::Tape::Head head(tape.setHead(0, Turing::State("q0")));
	Turing::Parser parser;
	Turing::Program program(parser.parse(&file));
	//std::cout << program << std::endl;

	std::cout << "              V" << std::endl;
	Turing::Command cmd;
	std::cout << head;

	do {
		cmd = program.command( head.state(), head.observable() );
		std::cout <<
			head.execute( cmd );
	}
	while (cmd != Turing::Command::STOP);
	std::cout << std::endl;
	
	return 0;
}