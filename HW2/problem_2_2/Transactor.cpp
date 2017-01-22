#include "Transactor.h"

void transactor::transactor_thread()
{
	int d;
	for (;;){
		wait(clk->negedge_event());
		D->write(0);

		if (LD->read() == true && RW->read() == true){//read
			m_mem->word_read(X->read(), Y->read(), d);
			D->write(d);
			//printf("in\n");
			wait(clk->negedge_event());
		}
		else if (LD->read() == true && RW->read() == false){//write
			m_mem->word_write(X->read(), Y->read(), D->read().to_long());
			//printf("in\n");
			if (X->read() == 7 && Y->read() == 7) {
				//printf("Debug\n");
				m_mem->notify();
				break;
			}
			wait(clk->negedge_event());
		}
	}
}
