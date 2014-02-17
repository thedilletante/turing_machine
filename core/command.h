#ifndef _TURING_MACHINE_COMMAND
#define _TURING_MACHINE_COMMAND

#include "cell.h"

namespace Turing {

struct Command {

public:
	enum Direction { INIT, STOP, LEFT, RIGHT };

	// constructor
	Command(const Direction&, const Cell::symbol&);
	Command();

	// getters
	const Direction& direction() const;
	const Cell::symbol& change() const;

private:
	Direction d;
	Cell::symbol c;

}; // struct Command

// inline

inline Command::Command(const Direction& direct, const Cell::symbol& sym) : d(direct), c(sym) {}
inline Command::Command() : d(Command::INIT) {}
inline const Command::Direction& Command::direction() const { return d; }
inline const Cell::symbol& Command::change() const { return c; }

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