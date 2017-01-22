
#ifndef LAB1_STIMULUS
#define LAB1_STIMULUS

#include <systemc.h>

SC_MODULE( Stimulus ) {

    // Port declaration
    sc_in_clk 			iclk;
    sc_out< bool >	Reset;
    sc_out< bool >	Enable;
    sc_out< bool >  UpDown;

    // Channel, submodules declaration

    // Constructor declaration
    SC_HAS_PROCESS( Stimulus );
    Stimulus( sc_module_name mn );

    // Process declaration
    void process_thread( void );

    // Helper declartion

    // Private data

};

#endif

