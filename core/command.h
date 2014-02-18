#ifndef _TURING_MACHINE_COMMAND
#define _TURING_MACHINE_COMMAND

#include "tape.h"
#include "state.h"

namespace Turing {

struct Command {

public:
	enum Direction { STOP, LEFT, RIGHT };

	// constructor
	Command(const Direction&, const Tape::symbol&, const State&);

	// getters
	const Direction& direction() const;
	const Tape::symbol& change() const;
	const State& state() const;

private:
	Direction d;
	Tape::symbol c;
	State s;

}; // struct Command

// inline

inline Command::Command(const Direction& direct, const Tape::symbol& sym, const State& st) : d(direct), c(sym), s(st) {}
inline const Command::Direction& Command::direction() const { return d; }
inline const Tape::symbol& Command::change() const { return c; }
inline const State& Command::state() const { return s; }

inline bool operator==(const Command& cmd, const Command::Direction& dir) {
	return cmd.direction() == dir;
}
inline bool operator==(const Command::Direction& dir, const Command& cmd) {
	return cmd.direction() == dir;
}
inline bool operator!=(const Command& cmd, const Command::Direction& dir) {
	return !(cmd == dir);
}
inline bool operator!=(const Command::Direction& dir, const Command& cmd) {
	return !(cmd == dir);
}

} // namespace Turing

#endif // _TURING_MACHINE_COMMAND