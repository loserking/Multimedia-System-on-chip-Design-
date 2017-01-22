
#ifndef	SYSTEMC_LAB1_DISPLAY
#define SYSTEMC_LAB1_DISPLAY

#include <systemc.h>

SC_MODULE( Display ) {

    // Port declaration
    sc_in<int> Value;

    // Channel, submodules declaration

    // Constructor declaration
    SC_HAS_PROCESS( Display );
    Display( sc_module_name mn );

    // Process declaration
    void process_method( void );

    // Helper declartion

    // Private data
    int old_value;
};

#endif

