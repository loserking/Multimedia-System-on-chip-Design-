#include <time.h>
#include <iomanip>

#include "Memory.h"

memory::memory(sc_module_name _name) : sc_channel(_name){
	srand(time(NULL));
	//allocate memory
	m_mem = new int*[8];
	for (int i = 0; i < 8; i++){
		m_mem[i] = new int[8];
	}

	//Generate memory data randomly
	cout << "Original data in Memory." << endl;
	for (int i = 0; i < 8; i++){
		cout << " [ ";
		for (int j = 0; j < 8; j++){
			m_mem[i][j] = rand() % 100;
			cout << std::setw(3) << m_mem[i][j] << " ";
		}
		cout << " ] " << endl;
	}

	SC_THREAD(memory_operation);
}

void memory::word_read(unsigned x, unsigned y, int& d)
{
	d = m_mem[x][y];
}

void memory::word_write(unsigned x, unsigned y, int d)
{
	m_mem[x][y] = d;
}

void memory::memory_operation()
{
	wait(m_interrupt);
	//wait(clk->negedge_event());
	cout << "New data in Memory." << endl;
	for (int i = 0; i < 8; i++){
		cout << " [ ";
		for (int j = 0; j < 8; j++){
			cout << std::setw(3) << m_mem[i][j] << " ";
		}
		cout << " ] " << endl;
	}

}