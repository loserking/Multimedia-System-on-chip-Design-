//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See fifo_fir.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
using std::cout;
using std::endl;

#include <systemc.h>
#include "fifo_fir.h"
#include "stimulus.h"
#include "results.h"

#define clockcycle   10  //10ns=100MHz

unsigned errors = 0;
char* simulation_name = "fifo_fir";

int sc_main(int argc, char* argv[]) {
	//sc_set_time_resolution(1,SC_PS);
	//sc_set_default_time_unit(1,SC_NS);
	sc_signal   <double>  orig_in;
	sc_signal   <double>  data_in;
	sc_signal   <double>  data_out;
	sc_time     stim_t(300, SC_NS);
	sc_clock    clk("clk", clockcycle, 0.5, 0, SC_NS);


	fifo_fir sc_fifo_ex_i("sc_fifo_ex_i");
	sc_fifo_ex_i.clk(clk);
	sc_fifo_ex_i.data_in(data_in);
	sc_fifo_ex_i.data_out(data_out);

	stimulus stimulus_i("stimulus_i");
	stimulus_i.clk(clk);
	stimulus_i.data_in(data_in);
	stimulus_i.orig_in(orig_in);

	results results_i("results_i");
	results_i.clk(clk);
	results_i.data_out(data_out);
	results_i.orig_in(orig_in);

	sc_trace_file* tracefile;
	tracefile = sc_create_vcd_trace_file("waveform");

	sc_trace(tracefile, clk, "clk");
	sc_trace(tracefile, orig_in, "orig_in");
	sc_trace(tracefile, data_in, "data_in");
	sc_trace(tracefile, data_out, "data_out");

	cout << "INFO: Starting " << simulation_name << " simulation" << endl;
	if (errors == 0) sc_start(stim_t);
	cout << "INFO: Exiting " << simulation_name << " simulation" << endl;
	cout << "INFO: Simulation " << simulation_name
		<< " " << (errors ? "FAILED" : "PASSED")
		<< " with " << errors << " errors"
		<< endl;

	sc_close_vcd_trace_file(tracefile);

	system("pause");
	return errors ? 1 : 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/24 17:21:26 dcblack Exp $
