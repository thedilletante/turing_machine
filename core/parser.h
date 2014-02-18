#ifndef _TURING_MACHINE_PARSER
#define _TURING_MACHINE_PARSER

#include <iostream>
#include <map>
#include "program.h"
#include "state.h"
#include "command.h"
#include "tape.h"

namespace Turing {

class Parser {
public:
	class Syntax_error {};

	Parser(const char& delimeter = '\n') : DELIMETER(delimeter) {}

	// interface
	Program& parse(std::istream*);

private:
	std::map< std::istream*, Program > cache;
	const char DELIMETER;

	std::istream* current;
	std::map< std::string, State > states;
	int counter;


	const State& state();
	const Tape::symbol symbol();
	void arrow();
	const Command::Direction dir();
	void separator();
};

// helpers
#include <cctype>
inline void skip(std::istream* input) {
	char ch;
	do {
		if (!input->get(ch)) return;
	} while (isspace(ch));
	input->putback(ch);
}

// inline
inline const State& Parser::state() {
	std::string state;
	char ch;
	while (current->get(ch)) {
		if (isspace(ch)) break;
		else if (isalnum(ch)) state.push_back(ch);
		else throw Syntax_error();
	}
	if (state.empty()) throw Syntax_error();
	std::map< std::string, State>::iterator i = states.find( state );
	if (i != states.end()) return i->second;
	return states[state] = ++counter;
}

inline const Tape::symbol Parser::symbol() {
	Tape::symbol ch;
	if (!current->get(ch)) throw Syntax_error();
	return ch;
}

inline void Parser::arrow() {
	char ch1, ch2;
	if (!current->get(ch1) || !current->get(ch2)) throw Syntax_error();
	if (ch1 == '-' && ch2 == '>') return;
	throw Syntax_error();
}

inline const Command::Direction Parser::dir() {
	char ch;
	char del = ch;
	if (!current->get(ch)) return Command::STOP;
	switch(ch) {
		case 'R': return Command::RIGHT;
		case 'L': return Command::LEFT;
		case 'S': return Command::STOP;
		default:
			current->putback(ch);
			return Command::STOP;
	}
}

inline void Parser::separator() {
	if (isspace(DELIMETER)) return;
	char ch;
	if (current->get(ch) && ch != DELIMETER) throw Syntax_error();
}



inline Program& Parser::parse(std::istream* input) {
	if (input == 0) throw Syntax_error();
	std::map< std::istream*, Program >::iterator i = cache.find( input );
	if (i != cache.end()) return i->second;
	Program& program = cache[input];
	current = input;
	counter = -1;


	while (!input->eof()) {
		skip(current); const State& cur_state = state();
		skip(current); const Tape::symbol observ = symbol();
		skip(current); arrow();
		skip(current); const State& s_change = state();
		skip(current); const Tape::symbol sym_change = symbol();
		skip(current); const Command::Direction direction = dir();
		skip(current); separator(); skip(current);

		program.add_command(cur_state, observ, Command(s_change, sym_change, direction));
	}

	current = 0;
	states.clear();
	return program;
}

} // namespace Turing

#endif // _TURING_MACHINE_PARSER