turing_machine
==============

Simulator of the Turing machine


testing:
	cd core
	mkdir build
	cd build
	cmake ..
	make
	./turing -P ../test -t "((())())" -S q0 -d _