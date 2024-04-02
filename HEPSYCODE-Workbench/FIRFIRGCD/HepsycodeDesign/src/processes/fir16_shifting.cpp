
#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//f16s
void mainsystem::fir16_shifting()
{
	// datatype for channels
	fir16s_parameters fir16s_p;
	fir16s_results fir16s_r;

	// local variables
	sc_uint<8> sample_tmp;
	sc_uint<8> shift[16];

	while(1)
	{

		// read parameters from channel
		fir16s_p=fir16s_parameters_channel->read();

		// fill local variables
		sample_tmp=fir16s_p.sample_tmp;
		for( unsigned j=0; j<TAP16; j++) shift[j]=fir16s_p.shift[j];

		// process

		for(int i=TAP16-2; i>=0; i--)
		{
			shift[i+1] = shift[i];
		}

		shift[0]=sample_tmp;

		// fill datatype
		for (unsigned j = 0; j < TAP16; j++)
		{
			fir16s_p.shift[j] = shift[j];
		}

		// send results by channel
		fir16s_results_channel->write(fir16s_r);
	}
}
