#include <systemc.h>

SC_MODULE(results) {
	sc_in  <double>   orig_in;
	sc_in  <double>   data_out;
	sc_in_clk         clk;

	SC_HAS_PROCESS(results);
	// Constructor
	SC_CTOR(results){
		SC_THREAD(results_thread);
		sensitive << clk.neg();
	}
	// Destructor

	// Processes
	void results_thread(void);
};