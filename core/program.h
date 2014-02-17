#ifndef _TURING_MACHINE_PROGRAM
#define _TURING_MACHINE_PROGRAM

#include <map>
#include "command.h"
#include "cell.h"
#include "head.h"

namespace Turing {

class Program {

public:
	// exceptions
	class Command_not_found {};

	// constructors
	Program();

	// interface
	const Command& command(const State&, const Cell::symbol&) const;

private:
	typedef std::map< Cell::symbol, Command > smap;
	typedef std::map< State, smap > cmap;
	cmap contaiter;

}; // class Program

// inline
inline Program::Program() {}

inline const Command& Program::command(const State& st, const Cell::symbol& sym) const {
	cmap::const_iterator s_map = contaiter.find( st );
	if (s_map != contaiter.end()) {
		smap::const_iterator cmd = s_map->second.find( sym );
		if (cmd != s_map->second.end()) return cmd->second;
	}
	throw Command_not_found();
}

} // namespace Turing

#endif // _TURING_MACHINE_PROGRAM