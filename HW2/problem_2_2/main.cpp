#include "systemc.h"
#include <iostream>

#include "Interchange.h"
#include "Memory.h"
#include "Transactor.h"

#define clockcycle   10     //10ns=100MHz
#define stim_len     3000   //ns

unsigned errors = 0;
char* simulation_name = "problem_2_2";

int sc_main(int argc, char* argv[]) {
	sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_, SC_DO_NOTHING);
	sc_time     stim_t(stim_len, SC_NS);
	sc_clock    clk("clk", clockcycle, 0.5, 0, SC_NS);
	sc_signal<bool>      LD;
	sc_signal<bool>      RW;
	sc_signal<unsigned>  X;
	sc_signal<unsigned>  Y;
	sc_signal_rv<32>     D;

	memory memory_i("memory_i");

	transactor transactor_i("transactor_i");
	transactor_i.clk(clk);
	transactor_i.LD(LD);
	transactor_i.RW(RW);
	transactor_i.X(X);
	transactor_i.Y(Y);
	transactor_i.D(D);
	transactor_i.m_mem(memory_i);

	interchange interchange_i("interchange_i");
	interchange_i.clk(clk);
	interchange_i.LD(LD);
	interchange_i.RW(RW);
	interchange_i.X(X);
	interchange_i.Y(Y);
	interchange_i.D(D);

	cout << "INFO: Simulating " << simulation_name << endl;
	sc_start(stim_t);
	cout << "INFO: Post-processing " << simulation_name << endl;
	cout << "INFO: Simulation " << simulation_name
		<< " " << (errors ? "FAILED" : "PASSED")
		<< " with " << errors << " errors"
		<< endl;

	system("pause");
	return errors ? 1 : 0;
}