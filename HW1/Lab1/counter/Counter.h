
#ifndef SYSC_UP_DOWN_COUNTER
#define SYSC_UP_DOWN_COUNTER

#include <systemc.h>

SC_MODULE( Counter ) {

    // Port declaration
    sc_in_clk    iclk;   // postive edge triggerd
    sc_in<bool>  Reset;  // true for reset
    sc_in<bool>  Enable; // true for counting
    sc_in<bool>  UpDown; // ture for count up
    sc_out<int>  Value;

    // Channel, submodules declaration

    // Constructor declaration
    SC_CTOR( Counter ) {              // registration the constructor of "Counter"
        SC_METHOD( process_method );  // registration entry() as event handler
        dont_initialize();            // method entry() is not made runnable during initialization
        sensitive << iclk.pos();      // entry() is triggered at positive edge of Clock
        v = 0;                        // give counter initial value
    }

    // Process declaration
    void process_method( void );

    // Helper declartion

    // Private data
    int  v;


};

#endif
