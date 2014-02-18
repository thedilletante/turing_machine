#ifndef _TURING_MACHINE_PROGRAM
#define _TURING_MACHINE_PROGRAM

#include <map>
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

} // namespace Turing

#endif // _TURING_MACHINE_PROGRAM