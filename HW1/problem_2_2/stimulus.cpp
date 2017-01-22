#include "stimulus.h"  


void stimulus::stimulus_thread(void) {
	unsigned PTS = 20;
	for (unsigned t = 0; t<PTS; t++) {
		double data = 0.0;
		if (t >= 8 && t<=12) data = 1.0; // step

		orig_in.write(data);
		data_in.write(data);
		wait();
	}//endfor
}//end stimulus_thread()