#include "tape.h"
#include "state.h"
#include "command.h"
#include "program.h"
#include <iostream>

int main() {
	// build a program
	// read a tape
	// install firts position of head
	// program cycle




	Turing::Tape tape('_', 3);
	tape.load('a').load('_').load('_');

	Turing::Tape::Head head(tape.setHead(-10, Turing::State('a')));
	Turing::Program program;

	Turing::Command cmd;

	do {
		cmd = program.command( head.state(), head.observable() );
		std::cout <<
			head.execute( cmd )
		<< std::endl;
	}
	while (cmd != Turing::Command::STOP);
	
	return 0;
}