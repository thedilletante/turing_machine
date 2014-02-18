#ifndef _TURING_MACHINE_PROGRAM
#define _TURING_MACHINE_PROGRAM

#include <map>
#include "command.h"
#include "tape.h"

namespace Turing {

class Program {

public:
	// exceptions
	class Command_not_found {};

	// constructors
	Program();

	// interface
	Command command(const State&, const Tape::symbol&) const;

private:
	typedef std::map< Tape::symbol, Command > smap;
	typedef std::map< State, smap > cmap;
	cmap contaiter;

}; // class Program

// inline
inline Program::Program() {
	contaiter[State('a')]['_'] = Command(Command::RIGHT, '_', State('a'));
	contaiter[State('a')]['a'] = Command(Command::STOP, '_', State('a'));
}

inline Command Program::command(const State& st, const Tape::symbol& sym) const {
	cmap::const_iterator s_map = contaiter.find( st );
	if (s_map != contaiter.end()) {
		smap::const_iterator cmd = s_map->second.find( sym );
		if (cmd != s_map->second.end()) return cmd->second;
	}
	throw Command_not_found();
}

} // namespace Turing

#endif // _TURING_MACHINE_PROGRAM