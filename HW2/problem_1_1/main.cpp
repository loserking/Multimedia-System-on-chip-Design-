#include "systemc.h"
#include <iostream>

#include "Interchange.h"
#include "Memory.h"

unsigned errors = 0;
char* simulation_name = "problem_1_1";

int sc_main(int argc, char* argv[]) {
	memory memory_i("memory_i");
	interchange interchange_i("interchange_i");
	interchange_i.m_mem(memory_i);

	cout << "INFO: Simulating " << simulation_name << endl;
	sc_start();
	cout << "INFO: Post-processing " << simulation_name << endl;
	cout << "INFO: Simulation " << simulation_name
		<< " " << (errors ? "FAILED" : "PASSED")
		<< " with " << errors << " errors"
		<< endl;

	system("pause");
	return errors ? 1 : 0;
}