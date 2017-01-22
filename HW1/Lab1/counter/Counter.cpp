
#include "Counter.h"

void  Counter::process_method( void ) {
    /*- Write the behavior code of the up/down counter here -*/
    if( Reset.read() == true ) {
        // reset to zero
        v = 0;    
    }
    else if( Enable.read() == true ) {
		if (UpDown.read() == true) {
			v = (v == 15) ? 15 : v + 1;
		}
		else {
			v = (v == 0) ? 0 : v - 1;
		}
	}
	else {
		v = v;
    }

    // cout << "Counter::process_method " << sc_time_stamp() << " Value = " << Value.read() << " , v = " << v << endl;

    Value.write( v ); // update the output signal
}