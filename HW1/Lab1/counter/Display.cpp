
#include "Display.h"
#include <iostream>

using std::cout;
using std::endl;

Display::Display( sc_module_name mn )
    : sc_module( mn ), old_value( 0 )
{	// process registration and sensitivity
	SC_METHOD(process_method);
	sensitive << Value;
}

void Display::process_method( void ) 
{
    if( old_value != Value.read() )
    {
        cout << "Updated to " << Value.read() << " at " << sc_time_stamp() << endl;	
        old_value = Value.read();
    }
    else
        cout << "Hold old value" << endl;	// Please observe if this statement will be executed
}


