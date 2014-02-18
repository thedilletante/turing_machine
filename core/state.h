#ifndef _TURING_MACHINE_STATE
#define _TURING_MACHINE_STATE

namespace Turing {

struct State{
public:
	typedef char name;

	// constructors
	State(const name& n) : _n(n) {}
	State() : _n('\0') {}

	bool operator<(const State& s) const { return _n < s._n; }
private:
	name _n;
}; // struct State

} // namespace Turing

#endif // _TURING_MACHINE_HEAD