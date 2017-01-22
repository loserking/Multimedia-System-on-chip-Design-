#include "Transactor.h"

void transactor::word_read(unsigned x, unsigned y, int& d)
{
	wait(clk->posedge_event());
	LD->write(true);
	RW->write(true);
	X->write(x);
	Y->write(y);
	wait(clk->posedge_event());
	LD->write(false);
	d = D->read().to_long();
}

void transactor::word_write(unsigned x, unsigned y, int d)
{
	wait(clk->posedge_event());
	LD->write(true);
	RW->write(false);
	X->write(x);
	Y->write(y);
	D->write(d);
	wait(clk->posedge_event());
	LD->write(false);
}
