 
#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//f8s
void mainsystem::fir8_shifting()
{
	// datatype for channels
	fir8s_parameters fir8s_p;
	fir8s_results fir8s_r;

	// local variables
	sc_uint<8> sample_tmp;
	sc_uint<8> shift[8];

	while(1)
	{

		// read parameters from channel
		fir8s_p=fir8s_parameters_channel->read();

		// fill local variables
		sample_tmp=fir8s_p.sample_tmp;

		for (unsigned j = 0; j < TAP8; j++)
		{
			shift[j] = fir8s_p.shift[j];
		}

		// process

		for(int i=TAP8-2; i>=0; i--)
		{
			shift[i+1] = shift[i];
		}

		shift[0]=sample_tmp;

		// fill datatype
		for( unsigned j=0; j<TAP8; j++) fir8s_p.shift[j]=shift[j];

		// send results by channel
		fir8s_results_channel->write(fir8s_r);
	}
}
