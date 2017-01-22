#ifndef INTERCHANGE_H
#define INTERCHANGE_H

#include "systemc.h"
#include "Memory.h"
#include "Mem_if.h"

SC_MODULE(interchange){
	sc_in_clk         clk;
	sc_out<bool>      LD;
	sc_out<bool>      RW;
	sc_out<unsigned>  X;
	sc_out<unsigned>  Y;
	sc_inout_rv<32>   D;


	SC_HAS_PROCESS(interchange);
	interchange(sc_module_name _name);

	void interchange_thread();

private:
	int **mem_inter;
};

#endif