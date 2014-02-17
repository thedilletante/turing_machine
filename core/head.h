#ifndef _TURING_MACHINE_HEAD
#define _TURING_MACHINE_HEAD

#include "cell.h"
#include "command.h"

namespace Turing {

struct State{
public:
	typedef char name;

	// constructors
	State(const name& n) : _n(n) {}

	bool operator<(const State& s) const { return _n < s._n; }
private:
	name _n;
};

class Head {

public:

	// constructors
	Head(Cell*, const State&);

	// getters
	const State& state() const;
	const Cell::symbol& observable() const;
	Head& execute(const Command&);

private:
	Cell* cur;
	State st;
}; // class Head

// inline
inline Head::Head(Cell* start, const State& state) : cur(start), st(state) {}

inline const State& Head::state() const { return st; }
inline const Cell::symbol& Head::observable() const { return cur->sym(); }

inline Head& Head::execute(const Command& cmd) {
	cur->set( cmd.change() );
	switch( cmd.direction() ) {
		case Command::LEFT:
			cur = cur->leftCell();
			break;
		case Command::RIGHT:
			cur = cur->rightCell();
			break;
		// nothing to do
		case Command::STOP:
		default:
			break;
	}
	return *this;
}

} // namespace Turing

#endif // _TURING_MACHINE_HEAD