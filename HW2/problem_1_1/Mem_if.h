#ifndef MEM_IF_H
#define MEM_IF_H

#include "systemc.h"

class mem_if : virtual public sc_interface {
public:
	//Functional model
	virtual void direct_read(int** block) = 0;
	virtual void direct_write(int** block) = 0;

	//delay notification
	virtual void notify() = 0;
	virtual const sc_event& default_event() const = 0;

};

#endif