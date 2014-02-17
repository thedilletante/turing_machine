#ifndef _TURING_MACHINE_TAPE
#define _TURING_MACHINE_TAPE

#include <vector>
#include <iostream>
#include "cell.h"

namespace Turing {

class Tape {

private:

	typedef std::vector< Cell::symbol > svector;
	typedef std::vector< Cell* > cell_vector;

public:

	// constructors
	Tape();
	Tape(const svector&);

	~Tape();

	// getters
	size_t size() const;

	// loaders
	//Tape& load(const svector&, int);
	//Tape& load(const Cell::symbol&, int);

	// prints
	friend std::ostream& operator<<(std::ostream&, const Tape&);

private:
	Cell* lCell;
	size_t s;
	size_t iterator;
	cell_vector container;

	Cell* rewind(int count, Cell* (Cell::*dir))

}; // class Tape

// inline

inline Tape::Tape() : lCell(0), s(0), iterator(0) {}
inline Tape::~Tape() {
	typedef cell_vector::iterator iter;
	for (iter i = container.begin(), end = container.end(); i != end; ++i)
		delete *i;
}

inline size_t Tape::size() const { return iterator; }


} // namespace Turing

#endif // _TURING_MACHINE_TAPE