#include <systemc.h>
#include "consumer.h"

consumer::consumer(sc_module_name name) 
    : sc_module(name)
{
    SC_THREAD(main);
}

void consumer::main()
{
    char c;

	while (true) {
		if (in->isEmpty()){
			cout << "Read: Blocking from " << sc_time_stamp();
			in->read(c);
			cout << " to " << sc_time_stamp() << "." << endl;
		}
		else{
			cout << "Read: Nonblocking from " << sc_time_stamp();
			in->read(c);
			cout << " to " << sc_time_stamp() << "." << endl;
		}
        in->read(c);
        wait(100, SC_NS);
    }
}
