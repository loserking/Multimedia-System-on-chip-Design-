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

void memory::direct_read(int** block)
{
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			block[i][j] = m_mem[i][j];
		}
	}
}

void memory::direct_write(int** block)
{
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			m_mem[i][j] = block[i][j];
		}
	}
}

void memory::memory_operation()
{
	wait(m_interrupt);
	cout << "New data in Memory." << endl;
	for (int i = 0; i < 8; i++){
		cout << " [ ";
		for (int j = 0; j < 8; j++){
			cout << std::setw(3) << m_mem[i][j] << " ";
		}
		cout << " ] " << endl;
	}
}