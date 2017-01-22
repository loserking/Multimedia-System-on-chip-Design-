#ifndef TRANSACTOR_H
#define TRANSACTOR_H

#include "systemc.h"
#include "Mem_if.h"

SC_MODULE(transactor){
	sc_in_clk        clk;
	sc_in<bool>      LD;
	sc_in<bool>      RW;
	sc_in<unsigned>  X;
	sc_in<unsigned>  Y;
	sc_inout_rv<32>  D;
	sc_port<mem_if>  m_mem;

	SC_CTOR(transactor){
		SC_THREAD(transactor_thread);
		//sensitive << clk.pos();
	};

	//Processes
	//void word_read(unsigned x, unsigned y, int& d);
	//void word_write(unsigned x, unsigned y, int d);
	void transactor_thread();
};

#endif