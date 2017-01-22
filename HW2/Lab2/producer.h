#ifndef PRODUCER_H
#define PRODUCER_H

#include <systemc.h>
#include "write_if.h"

class producer : public sc_module
{
public:
    sc_port<write_if> out;

    SC_HAS_PROCESS(producer);

    producer(sc_module_name name);

    void main();
};

#endif

