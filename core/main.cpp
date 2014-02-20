#include "tape.h"
#include "state.h"
#include "command.h"
#include "parser.h"
#include "console_printer.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <boost/program_options.hpp>

int main(int argc, char *argv[]) {

	namespace po = boost::program_options;

	std::string p_file_name;
	std::string t;
	std::string state;
	int latency = 700000;
	int position = 0;
	char def = ' ';
	int qnt = 15;

	std::string d("Program options");
	po::options_description desc(d.c_str());
	desc.add_options()
	    ("program,P", po::value< std::string >(&p_file_name), "source files")
	    ("tape,t", po::value< std::string >(&t), "file or line to set tape of symbols, cin by default")
	    ("state,S", po::value< std::string >(&state), "start state of head")
	    ("position,p", po::value< int >(&position), "position of head, 0 by default")
	    ("default,d", po::value< char >(&def), "default symbol, space ' ' by default" )
	    ("latency,l", po::value< int >(&latency), "latency for show program work, 700000ms by default (don't work with -s options)")
	    ("quantity,q", po::value< int >(&qnt), "quantity of showed tape, 15 by default (don`t work with -s options)")
	    ("silence,s", "show only result")
	    ("verbose,v", "By more verbose")
	    ("help,h", "show this help and exit")
	;

	po::positional_options_description pod;
	pod.add("program", -1);

	po::variables_map vm;
	try {
		po::store(po::command_line_parser(argc, argv).
			options(desc).positional(pod).run(), vm);
		po::notify(vm); 
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}   

	if (vm.count("help") || !vm.count("program") || !vm.count("state")) {
	    std::cout << desc << "\n";
	    return 1;
	}

	std::ifstream file(p_file_name.c_str());

	Turing::Tape tape(def);
	std::istream* input;
	if (vm.count("tape")) {
		std::ifstream* finput = new std::ifstream(t.c_str());
		if (!finput->is_open()) {
			delete finput;
			t.push_back('\0');
			input = new std::stringstream(t);
		}
		else input = finput;
	}
	else input = &std::cin;

	Turing::Tape::symbol ch, prev = '\0';
	while(input->get(ch)) {
		if (prev) tape.load(prev);
		prev = ch;
	}

	if (input != &std::cin) delete input;

	Turing::Tape::Head head(tape.setHead(position, Turing::State(state)));
	Turing::Parser parser;
	Turing::Program program(parser.parse(&file));
	if (vm.count("verbose")) std::cout << program;

	Turing::Command cmd;
	ConsolePrinter p(head, &std::cout);

	bool silence = vm.count("silence");
	if (qnt < 0) qnt = -qnt;
	else if (qnt == 0) qnt = 15;
	if (!silence) p.print(qnt, latency);

	do {
		cmd = program.command( head.state(), head.observable() );
		head.execute( cmd );
		if (!silence) p.print(qnt, latency);
	}
	while (cmd != Turing::Command::STOP);
	
	if (silence) std::cout << tape;
	std::cout << std::endl;
	
	return 0;
}