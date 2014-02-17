#ifndef _TURING_MACHINE_CELL
#define _TURING_MACHINE_CELL

namespace Turing {

class Cell {

public:
	typedef char symbol;

private:
	const static symbol DEFAULT_SYMBOL = ' ';

public:
	// constructors
	Cell(const symbol& sym = DEFAULT_SYMBOL);

	// getters
	const symbol& sym() const;
	Cell* rightCell() const;
	Cell* leftCell() const;

	// manipulate
	Cell& set(const symbol&);

private:

	symbol s;
	Cell* r;
	Cell* l;


}; // class Cell

// inline
inline Cell::Cell(const symbol& sym) : s(sym), r(0), l(0) {}

inline const Cell::symbol& Cell::sym() const { return s; };
inline Cell* Cell::rightCell() const { return r; } // if r or l = 0, need to glue more elements from tape
inline Cell* Cell::leftCell() const { return l; }

inline Cell& Cell::set(const Cell::symbol& sym) { s = sym; return *this; }

} // namespace Turing

#endif // _TURING_MACHINE_CELL