#ifndef FIFO_H
#define FIFO_H

#include <systemc.h>
#include "write_if.h"
#include "read_if.h"

class fifo : public sc_channel, public write_if, public read_if
{
public:
    fifo(sc_module_name name, int size_);
    ~fifo();
    void write(char c);
    void read(char &c);
    void reset();
    int num_available();
	bool isFull();
	bool isEmpty();

private:
    char *data;
    int num_elements, first;
    sc_event write_event, read_event;
    int size, num_read, max_used, average;
    sc_time last_time;

    void compute_stats();
};

#endif