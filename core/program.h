#ifndef _TURING_MACHINE_PROGRAM
#define _TURING_MACHINE_PROGRAM

#include <map>
#include <iostream>
#include "command.h"
#include "tape.h"

namespace Turing {

class Parser;

class Program {

public:
	// exceptions
	class Command_not_found {};
	friend class Parser;

private:
	// constructors
	Program() {};

public:
	// interface
	Command command(const State&, const Tape::symbol&) const;

	friend std::ostream& operator<<(std::ostream&, const Program&);

private:
	typedef std::map< Tape::symbol, Command > smap;
	typedef std::map< State, smap > cmap;
	cmap contaiter;

	// Parser interface
	Program& add_command(const State&, const Tape::symbol&, const Command&);
	friend class std::map<std::istream*, Program>;

}; // class Program

inline Command Program::command(const State& st, const Tape::symbol& sym) const {
	cmap::const_iterator s_map = contaiter.find( st );
	if (s_map != contaiter.end()) {
		smap::const_iterator cmd = s_map->second.find( sym );
		if (cmd != s_map->second.end()) return cmd->second;
	}
	throw Command_not_found();
}

inline Program& Program::add_command(const State& st, const Tape::symbol& s, const Command& c) {
	contaiter[st][s] = c;
	return *this;
} 

inline std::ostream& operator<<(std::ostream& os, const Program& p) {
	for (Program::cmap::const_iterator i = p.contaiter.begin(), end = p.contaiter.end(); i != end; ++i)
		for (Program::smap::const_iterator j = i->second.begin(), jend = i->second.end(); j != jend; ++j) {
			os << "command: " << i->first.n() 
				<< " " << j->first << " -> " << j->second.state().n()
				<< " " << j->second.change() << " ";
			switch (j->second.direction()) {
				case Command::LEFT: os << "L"; break;
				case Command::RIGHT: os << "R"; break;
				case Command::STOP:
				default:
					os << "S";
					break;
			}
			std::cout << std::endl;
		}
	return os;
}

} // namespace Turing

#endif // _TURING_MACHINE_PROGRAM