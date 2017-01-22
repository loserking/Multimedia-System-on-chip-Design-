/*****************************************************************************

The following code is derived, directly or indirectly, from the SystemC
source code Copyright (c) 1996-2006 by all Contributors.
All Rights reserved.

The contents of this file are subject to the restrictions and limitations
set forth in the SystemC Open Source License Version 2.4 (the "License");
You may not use this file except in compliance with such restrictions and
limitations. You may obtain instructions on how to receive a copy of the
License at http://www.systemc.org/. Software distributed by Contributors
under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
ANY KIND, either express or implied. See the License for the specific
language governing rights and limitations under the License.

*****************************************************************************/

/*****************************************************************************

simple_fifo.cpp -- SystemC 2.0 Performance Modeling Example.

This example is derived from the design presented within
"An Introduction to System Level Modeling in SystemC 2.0"
By Stuart Swan, Cadence Design Systems.
Available at www.systemc.org

The system being modeled has a producer block that
sends characters to a consumer block via a fifo.
The fifo will suspend the producer or consumer as
necessary to insure all characters are reliably
delivered.

The consumer block will consume exactly one
character every 100 ns unless it is suspended
waiting for input from the fifo.

The producer block produces between one and
19 characters every 1000 ns unless it is
suspended waiting to write to the fifo.
On average, the producer block produces
one character every 100 ns (unless suspended by
the fifo) since a random linear distribution is 
used for the character count.

If the fifo size is sufficiently large, the average
transfer time per character will approach 100 ns
since the producer and consumer will rarely be
blocked. However, as the fifo size decreases,
the average transfer time will increase because
the producer will sometimes be suspended when
it writes (due to a full fifo) and the consumer
will sometimes be suspended when it reads 
(due to an empty fifo).

The fifo size can be set via a command line argument
when running this program. By default, the fifo size
is 10. When the design is simulated, one hundred
thousand characters are transferred from the 
producer to the consumer and then performance
statistics are displayed.

Using this system level model, determine the size
of the fifo needed to sustain:

A) An average transfer time of 110 ns per character
B) An average transfer time of 105 ns per character

Hint: The answer to (A) is between 10 and 20.

Original Author: Stuart Swan, Cadence Design Systems, 2001-06-18

*****************************************************************************/

/*****************************************************************************

MODIFICATION LOG - modifiers, enter your name, affiliation, date and
changes you are making here.

Name, Affiliation, Date:
Description of Modification:

*****************************************************************************/


#include <systemc.h>
#include "fifo.h"
#include "producer.h"
#include "consumer.h"

class top : public sc_module
{
public:
    fifo fifo_inst;
    producer prod_inst;
    consumer cons_inst;

    top(sc_module_name name, int size) 
        : sc_module(name) ,
        fifo_inst("Fifo1", size) , 
        prod_inst("Producer1") , 
        cons_inst("Consumer1")
    {
        prod_inst.out(fifo_inst);
        cons_inst.in(fifo_inst);
    }
};

int sc_main (int argc , char *argv[]) 
{
    int size = 10;

    if (argc > 1)
        size = atoi(argv[1]);

    if (size < 1)
        size = 1;

    if (size > 100000)
        size = 100000;

    top top1("Top1", size);
    sc_start(10,SC_US);
    return 0;
}
