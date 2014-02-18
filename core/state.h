#ifndef _TURING_MACHINE_STATE
#define _TURING_MACHINE_STATE

#include <string>

namespace Turing {

struct State{
public:
	typedef std::string name;

	// constructors
	State(const name& n) : _n(n) {}
	State() {}

	const name n() const { return _n; }

	bool operator<(const State& s) const { return _n < s._n; }
private:
	name _n;
}; // struct State

} // namespace Turing

#endif // _TURING_MACHINE_HEAD