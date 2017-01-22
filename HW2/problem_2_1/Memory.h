#ifndef MEMORY_H
#define MEMORY_H

#include "systemc.h"
//#include "Mem_if.h"

SC_MODULE(memory) {
	sc_in_clk        clk;
	sc_in<bool>      LD;
	sc_in<bool>      RW;
	sc_in<unsigned>  X;
	sc_in<unsigned>  Y;
	sc_inout_rv<32>  D;

	SC_HAS_PROCESS(memory);

	//constructor
	memory(sc_module_name _name);

	//destructor
	//~memory();

	//Functional model
	//void direct_read(int** block);
	//void direct_write(int** block);

	//void word_read(unsigned x, unsigned y, int& d);
	//void word_write(unsigned x, unsigned y, int d);

	//void notify() { m_interrupt.notify(); }
	//const sc_event& default_event() const { return m_interrupt; }

	void memory_operation();
private:
	//sc_event m_interrupt;
	int **m_mem;
};

#endif