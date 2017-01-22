#ifndef CONSUMER_H
#define CONSUMER_H

#include <systemc.h>
#include "read_if.h"

class consumer : public sc_module
{
public:
    sc_port<read_if> in;

    SC_HAS_PROCESS(consumer);

    consumer(sc_module_name name);

    void main();

};

#endif

