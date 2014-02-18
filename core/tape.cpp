#include "tape.h"

Turing::Tape::Head Turing::Tape::setHead(int position, const Turing::State& st) {
	std::list< symbol >::iterator iter(tape.begin());
	if (position > 0) {
		for (int i = 0; i < position; ++i) {
			if (iter == tape.end()) add_to_end();
			iter++;
		}
	}
	else if (position < 0) {
		for (int i = 0; i > position; --i) {
			if (iter == tape.begin()) add_to_begin();
			iter--;
		}
	}
	return Head(this, iter, st);
}

#include "command.h"

Turing::Tape::Head& Turing::Tape::Head::execute(const Turing::Command& cmd) {
	*iter = cmd.change();
	s = cmd.state();
	switch (cmd.direction()) {
		case Command::LEFT:
			go_to_left();
			break;
		case Command::RIGHT:
			go_to_right();
			break;
		case Command::STOP:
		default:
			break;
	}
	return *this;
}

std::ostream& Turing::operator<<(std::ostream& os, const Turing::Tape::Head& head) {
	os << "      V\n";
	Tape::Head h(head);
	h.go_to_left().go_to_left().go_to_left();
	for (int i = 0; i < 7; ++i, h.go_to_right()) {
		os << *h.iter << " ";
	}
	return os << std::endl;
}