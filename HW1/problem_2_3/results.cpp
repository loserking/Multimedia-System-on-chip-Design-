#include "results.h"
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

void results::results_thread(void) {
	for (unsigned i = 0;; i++) {
		double data = orig_in.read();
		double result = data_out.read();
		cout << "DATA: "
			<< "[" << setw(2) << i << "]"
			<< "= " << setw(9) << fixed << setprecision(5) << data
			<< " " << setw(9) << fixed << setprecision(5) << result
			<< endl;
		wait();
	}//endforever
}//end results_thread()