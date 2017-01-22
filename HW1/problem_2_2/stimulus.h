#include <systemc.h>

SC_MODULE(stimulus) {
	sc_out  <double>   data_in;
	sc_out  <double>   orig_in;
	sc_in_clk          clk;

	SC_HAS_PROCESS(stimulus);
	// Constructor
	SC_CTOR(stimulus){
		SC_THREAD(stimulus_thread);
		sensitive << clk.neg();
	}
	// Destructor

	// Processes
	void stimulus_thread(void);
};