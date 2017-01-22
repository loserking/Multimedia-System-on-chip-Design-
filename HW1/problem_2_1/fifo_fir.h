#ifndef SC_FIFO_EX_H
#define SC_FIFO_EX_H
//BEGIN fifo_fir.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example uses threads to implement a FIR filter. Contrast this
//   with the method_fifo_fir example.
//
// Configuration file format:
//   +---------------------+
//   |N                    |
//   |COEFFICIENT_0        |
//   |COEFFICIENT_1        |
//   |COEFFICIENT_2        |
//   |...                  |
//   |COEFFICIENT_(N-1)    |
//   +---------------------+
//
// DESIGN HIERARCHY
//   sc_main()
//   +- sc_fifo_ex_i
//    +- stimulus_thread
//    +- sc_fifo_ex_thread
//    +- results_thread
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(fifo_fir) {
    sc_fifo<double> orig_in;
    sc_fifo<double> data_in;
    sc_fifo<double> data_out;
    double*     m_pipe;     // data pipe
    double*     m_coeff;    // array of coefficients
    unsigned m_taps;     // number of coefficients
    unsigned m_tap;      // current tap
    char* m_cfg_filename;
    SC_HAS_PROCESS(fifo_fir);
    // Constructor
    fifo_fir(sc_module_name _name, char* _cfg_filename="fifo_fir.cfg");
    // Destructor
    ~fifo_fir() {
        if (m_taps) {
            delete[] m_coeff;
            delete[] m_pipe;
        }//endif
    }//end ~fifo_fir()

    // Processes
    void stimulus_thread(void);
    void sc_fifo_ex_thread(void);
    void results_thread(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: fifo_fir.h,v 1.4 2004/04/15 17:38:57 dcblack Exp $
