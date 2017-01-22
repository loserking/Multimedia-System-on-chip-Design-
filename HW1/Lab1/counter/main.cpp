

#include <systemc.h>
#include "Counter.h"
#include "Stimulus.h"
#include "Display.h"

int sc_main( int argc, char** argv ) {

    /*-	Signal Declaration	-*/
    sc_time	        SIM_TIME( 500, SC_NS );
    sc_clock        clk ("clk", sc_time(10,SC_NS) );
    sc_signal<int>	Value;
    sc_signal<bool>	Enable;
    sc_signal<bool>	UpDown;
    sc_signal<bool> Reset;

    /*-	Instantiation and Net Connection	-*/
    Counter iCounter( "iCounter" );
    iCounter.iclk( clk );
	iCounter.Reset(Reset);
	iCounter.Enable(Enable);
	iCounter.UpDown(UpDown);
	iCounter.Value(Value);

    Stimulus iStimulus( "iStimulus"	);
    iStimulus.iclk( clk );
	iStimulus.Reset(Reset);
	iStimulus.Enable(Enable);
	iStimulus.UpDown(UpDown);
	Display iDisplay("iDisplay");
	iDisplay.Value(Value);

	sc_trace_file* tracefile;
	tracefile = sc_create_vcd_trace_file("wave");
	if (!tracefile) {
		printf("vcd file error");
		system("pause");
	}

	sc_trace(tracefile, clk, "clk");
	sc_trace(tracefile, Reset, "reset");
	sc_trace(tracefile, Enable, "Enable");
	sc_trace(tracefile, UpDown, "UpDown");
	sc_trace(tracefile, Value, "Value");

    /*-	Run Simulation	-*/
    sc_start( SIM_TIME );

    /*-	Clean Up	-*/	
    return 0;

}



