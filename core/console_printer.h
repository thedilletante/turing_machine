#ifndef _TURING_MACHINE_CONSOLE_PRINTER
#define _TURING_MACHINE_CONSOLE_PRINTER

#include <iostream>
#include <unistd.h>
#include "tape.h"

class ConsolePrinter {

public:
	ConsolePrinter(const Turing::Tape::Head& h, std::ostream* os) : head(h), out(os) {};

	ConsolePrinter& print(int qnt, int latency = 700000) {
		int aqnt = (qnt > 0) ? qnt : -qnt;
		int half = aqnt / 2;
		int doub = aqnt * 2;
		for (int i = 0; i < doub; ++i) *out << "\b";

		Turing::Tape::Head iter( head - half );
		for (int i = 0; i < aqnt; ++i, iter = iter + 1) {
			*out << iter.observable();
			if (i == half - 1) *out << "\x1b[31m" << "(" << "\x1b[0m";
			else if (i == half) *out << "\x1b[31m" << ")" << "\x1b[0m";
			else *out << " ";
		}

		*out << std::flush;
		usleep(latency);
		return *this;
	}

private:
	std::ostream* out;
	const Turing::Tape::Head& head;
};

#endif // _TURING_MACHINE_CONSOLE_PRINTER