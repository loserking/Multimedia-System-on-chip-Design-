#include <iomanip>
#include <systemc.h>
#include "Interchange.h"

interchange::interchange(sc_module_name nm){
	//allocate memory
	mem_inter = new int*[8];
	for (int i = 0; i < 8; i++){
		mem_inter[i] = new int[8];
	}

	SC_THREAD(interchange_thread);
}

void interchange::interchange_thread(){
	m_mem->direct_read(mem_inter);

	//interchage
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < (8 - i); j++){
			int temp;
			temp = mem_inter[i][j];
			mem_inter[i][j] = mem_inter[8 - j - 1][8 - i - 1];
			mem_inter[8 - j - 1][8 - i - 1] = temp;
		}
	}

	cout << "New data after interchage." << endl;
	for (int i = 0; i < 8; i++){
		cout << " [ ";
		for (int j = 0; j < 8; j++){
			cout << std::setw(3) << mem_inter[i][j] << " ";
		}
		cout << " ] " << endl;
	}

	//write back
	m_mem->direct_write(mem_inter);
	m_mem->notify();


}