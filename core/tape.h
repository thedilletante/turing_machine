#ifndef _TURING_MACHINE_TAPE
#define _TURING_MACHINE_TAPE

#include <vector>
#include <list>
#include <iostream>
#include "state.h"

namespace Turing {

class Tape {

public:
	typedef char symbol;
	typedef std::vector< symbol > svector;
	enum DIRECTION { LEFT, RIGHT };

	// constructors
	Tape(const symbol default_symbol = ' ', const size_t pushed = 50);
	Tape(const svector&, const symbol default_symbol = ' ', const size_t pushed = 50);

	// getters
	size_t size() const;

	// loaders
	//Tape& load(const svector&, const DIRECTION&);
	Tape& load(const symbol& s, const DIRECTION& d = RIGHT);

	// prints
	friend std::ostream& operator<<(std::ostream&, const Tape&);

	class Head;
	friend class Head;

	Head setHead(int, const State&);

private:
	typedef std::list< symbol > slist;
	slist tape;

	const symbol DEFAULT_SYMBOL;
	const size_t PUSHED;

	Tape& add_to_begin() { for (size_t i = 0; i < PUSHED; ++i) tape.push_front(DEFAULT_SYMBOL); return *this; }
	Tape& add_to_end() { for (size_t i = 0; i < PUSHED; ++i) tape.push_back(DEFAULT_SYMBOL); return *this; }

}; // class Tape


// inline
inline Tape::Tape(const symbol d, const size_t p) : DEFAULT_SYMBOL(d), PUSHED(p) {}

inline Tape::Tape(const Tape::svector& vector, const symbol d, const size_t p)
	: DEFAULT_SYMBOL(d), PUSHED(p) {
	for (Tape::svector::const_iterator i = vector.begin(), end = vector.end();
			i != end; ++i)
		tape.push_back( *i );
}

inline size_t Tape::size() const { return tape.size(); }

inline std::ostream& operator<<(std::ostream& os, const Tape& tape) {
	for (Tape::slist::const_iterator i = tape.tape.begin(), end = tape.tape.end();
			i != end; ++i)
		os << *i << ' ';
	return os;
}

inline Tape& Tape::load(const Tape::symbol& s, const Tape::DIRECTION& d) {
	if (d == LEFT) tape.push_front(s);
	else tape.push_back(s);
	return *this;
}

} // namespace Turing

namespace Turing {

class Command;

class Tape::Head {

public:
	const State& state() const;
	const symbol& observable() const;
	Head& execute(const Command&);

	friend std::ostream& operator<<(std::ostream& os, const Head&);

private:
	friend class Tape;
	Head(Tape* t, const std::list< symbol >::iterator& i, const State& st) : tape(t), iter(i), s(st) {}
	mutable Tape* tape;
	mutable std::list< symbol >::iterator iter;
	State s;

	Head& go_to_right();
	Head& go_to_left();

	Tape::slist& t() const { return tape->tape; }

}; // class Head


inline const State& Tape::Head::state() const { return s; }
inline const Tape::symbol& Tape::Head::observable() const {
	if (iter == t().end()) {
		--iter;
		tape->add_to_end();
		++iter;
	}
	return *iter;
}

inline Tape::Head& Tape::Head::go_to_right() {
	if (iter == tape->tape.end()) {
		--iter;
		tape->add_to_end();
		++iter;
	}
	++iter;
	return *this;
}
inline Tape::Head& Tape::Head::go_to_left() {
	if (iter == t().begin()) tape->add_to_begin();
	--iter;
	return *this;
}


}

#endif // _TURING_MACHINE_TAPE