#include <systemc.h>
#include "producer.h"

producer::producer(sc_module_name name) : sc_module(name)
{
    SC_THREAD(main);
}

void producer::main()
{
    const char *str =	"Visit www.systemc.org and see what SystemC can do for you today!\n";
    const char *p = str;
    int total = 100000;

    while (true)
    {
        int i = 1 + int(19.0 * rand() / RAND_MAX);  //  1 <= i <= 19

		while (--i >= 0)
		{
			if (out->isFull())
			{
				cout << "Write: Blocking from " << sc_time_stamp();
			out->write(*p++);
			cout << " to " << sc_time_stamp() << "," << endl;
			}
			else
			{
				cout << "Write: NonBlocking from " << sc_time_stamp();
				out->write(*p++);
				cout << " to " << sc_time_stamp() << "," << endl;
			}//out -> write(*p++)
            if (!*p) p = str;
            -- total;
        }

        if (total <= 0)
            break;

        wait(1000, SC_NS);
    }
}

