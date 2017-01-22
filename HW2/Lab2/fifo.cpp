#include <systemc.h>
#include "fifo.h"

fifo::fifo(sc_module_name name, int size_) : sc_channel(name), size(size_)
{
    data = new char[size];
    num_elements = first = 0;
    num_read = max_used = average = 0;
    last_time = SC_ZERO_TIME;
}

fifo::~fifo()
{
    delete[] data;

    cout << endl << "Fifo size is: " << size << endl;
    cout << "Average fifo fill depth: " << double(average) / num_read << endl;
    cout << "Maximum fifo fill depth: " << max_used << endl;
    cout << "Average transfer time per character: " 		<< last_time / num_read << endl;
    cout << "Total characters transferred: " << num_read << endl;
    cout << "Total time: " << last_time << endl;
}

void fifo::write(char c)
{
    if (num_elements == size)
        wait(read_event);

    data[(first + num_elements) % size] = c;
    ++ num_elements;
    write_event.notify();
}

void fifo::read(char &c)
{
    last_time = sc_time_stamp();
    if (num_elements == 0)
        wait(write_event);

    compute_stats();

    c = data[first];
    -- num_elements;
    first = (first + 1) % size;
    read_event.notify();
}

void fifo::reset() 
{ 
    num_elements = first = 0; 
}

int fifo::num_available()
{
	return num_elements;
}

bool fifo::isFull()
{
	return (num_elements == size);
}

bool fifo::isEmpty()
{
	return (num_elements == 0);
}

void fifo::compute_stats()
{
	average += num_elements;

	if (num_elements > max_used)
		max_used = num_elements;

	++num_read;
}


