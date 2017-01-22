
#include "Stimulus.h"

Stimulus::Stimulus( sc_module_name mn )
    : sc_module( mn )
{
    SC_THREAD( process_thread );
    sensitive << iclk.pos();	
}

void Stimulus::process_thread( void )
{	// initialization phase
    int i;
    Enable.write( false );
    Reset.write( false );
    UpDown.write( false );
    wait();

    // running phase
    Reset.write( true );
    wait();
    Reset.write( false );
    wait();

    Enable.write( true );
    UpDown.write( true );

    for(i=0;i<20;i++) 
        wait();		

    Enable.write( false );

    for(i=0;i<4;i++) 
        wait();		

    /*- Add count down test here -*/
	Enable.write(true);
	UpDown.write(false);

	for (i = 0; i<20; i++)
		wait();

	Enable.write(false);

	for (i = 0; i<4; i++)
		wait();

    for(;;)	// trap for keeping process alive
        wait();

}
