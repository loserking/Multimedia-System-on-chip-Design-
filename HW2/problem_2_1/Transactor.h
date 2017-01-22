#ifndef TRANSACTOR_H
#define TRANSACTOR_H

#include "systemc.h"
#include "Mem_if.h"

SC_MODULE(transactor), mem_if{
	sc_in_clk         clk;
	sc_out<bool>      LD;
	sc_out<bool>      RW;
	sc_out<unsigned>  X;
	sc_out<unsigned>  Y;
	sc_inout_rv<32>   D;

	SC_CTOR(transactor){
		//SC_THREAD(transactor_thread);
		//sensitive << clk.pos();
	}

	//Processes
	void word_read(unsigned x, unsigned y, int& d);
	void word_write(unsigned x, unsigned y, int d);
};

#endif