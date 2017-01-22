#ifndef INTERCHANGE_H
#define INTERCHANGE_H

#include "systemc.h"
#include "Memory.h"
#include "Mem_if.h"

SC_MODULE(interchange){
	sc_port<mem_if> m_mem;

	SC_HAS_PROCESS(interchange);
	interchange(sc_module_name _name);

	void interchange_thread();

private:
	int **mem_inter;
};

#endif