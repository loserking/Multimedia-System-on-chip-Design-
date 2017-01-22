//BEGIN fifo_fir.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See fifo_fir.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "fifo_fir.h"
#include <fstream>
#include <iomanip>
#include <cmath>

extern unsigned errors;
using std::cout;
using std::cerr;
using std::fixed;
using std::setw;
using std::setfill;
using std::setprecision;
using std::endl;

double Din_1, Dout_1, Din_2, Dout_2, Din_3,
Rout_1, Rout_2, Rout_3;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fifo_fir::fifo_fir(sc_module_name _name, char* _cfg_filename) :
sc_module(_name),
m_cfg_filename(_cfg_filename),
m_taps(0),
m_tap(0)
{
	SC_THREAD(sc_fifo_ex_thread1);
	sensitive << clk.pos();
	SC_THREAD(sc_fifo_ex_thread2);
	sensitive << clk.pos();
	SC_THREAD(sc_fifo_ex_thread3);
	sensitive << clk.pos();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Read coefficients from configuration file and initialize pipe to zero
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ifstream cfg_file(m_cfg_filename);
	if (!cfg_file) {
		cerr << "ERROR: Problem opening " << m_cfg_filename << " for input." << endl;
		errors++;
		return;
	}//endif
	cfg_file >> m_taps;
	//cout << m_taps << endl;
	if (m_taps < 1) {
		cerr << "ERROR: Number of taps must be greater than zero!" << endl;
		errors++;
		return;
	}//endif
	// Allocate memory
	m_pipe = new double[m_taps];
	m_coeff = new double[m_taps];
	for (unsigned tap = 0; tap != m_taps; tap++) {
		if (cfg_file.eof()) {
			cerr << "ERROR: Too few coefficients when reading [" << tap << "]." << endl;
			errors++;
			return;
		}//endif
		cfg_file >> m_coeff[tap];
		//cout << tap << "=" << m_coeff[tap] << endl;
		m_pipe[tap] = 0;
	}//endfor
}//end fifo_fir()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Processes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fifo_fir::sc_fifo_ex_thread1(void) {
	for (;;) {
		Dout_1 = m_pipe[2];
		for (int i = 2; i > 0; --i)
			m_pipe[i] = m_pipe[i - 1];
		m_pipe[0] = data_in.read();
		Din_1 = m_pipe[0];

		double result = 0.0;
		result += m_coeff[8] * m_pipe[0];
		result += m_coeff[7] * m_pipe[1];
		result += m_coeff[6] * m_pipe[2];
		Rout_1 = result;

		D_1_2.write(Dout_1);
		R_1_2.write(result);
		wait();
	}//endforever
}//end sc_fifo_ex_thread()

void fifo_fir::sc_fifo_ex_thread2(void) {
	for (;;) {
		Dout_2 = m_pipe[5];
		for (int i = 5; i > 3; --i)
			m_pipe[i] = m_pipe[i - 1];
		m_pipe[3] = D_1_2.read();
		Din_2 = m_pipe[3];

		double result = R_1_2.read();
		result += m_coeff[5] * m_pipe[3];
		result += m_coeff[4] * m_pipe[4];
		result += m_coeff[3] * m_pipe[5];
		Rout_2 = result;

		D_2_3.write(Dout_2);
		R_2_3.write(result);
		wait();
	}//endforever
}//end sc_fifo_ex_thread()

void fifo_fir::sc_fifo_ex_thread3(void) {
	for (;;) {
		for (int i = 8; i > 6; --i)
			m_pipe[i] = m_pipe[i - 1];
		m_pipe[6] = D_2_3.read();
		Din_3 = m_pipe[6];

		double result = R_2_3.read();
		result += m_coeff[2] * m_pipe[6];
		result += m_coeff[1] * m_pipe[7];
		result += m_coeff[0] * m_pipe[8];
		Rout_3 = result;

		data_out.write(result);
		wait();
	}//endforever
}//end sc_fifo_ex_thread()
