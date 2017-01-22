#ifndef MEMORY_H
#define MEMORY_H

#include "systemc.h"
#include "mem_if.h"

struct memory : public sc_channel, mem_if{

	SC_HAS_PROCESS(memory);

	//constructor
	memory(sc_module_name _name);


	void word_read(unsigned x, unsigned y, int& d);
	void word_write(unsigned x, unsigned y, int d);

	void notify() { m_interrupt.notify(); }
	const sc_event& default_event() const { return m_interrupt; }

	void memory_operation();
private:
	sc_event m_interrupt;
	int **m_mem;
};

#endif