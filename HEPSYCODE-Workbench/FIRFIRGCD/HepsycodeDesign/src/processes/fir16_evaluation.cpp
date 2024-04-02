
#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//f16e
void mainsystem::fir16_evaluation()
{
	// datatype for channels
	fir16e_parameters fir16e_p;
	fir16e_results fir16e_r;

	// local variables
	sc_int<17> pro;
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8>  sample_tmp;
	sc_uint<8> shift[16];

	while(1)
	{

		// read parameters from channel
		fir16e_p=fir16e_parameters_channel->read();

		// fill local variables
		sample_tmp=fir16e_p.sample_tmp;

		for (unsigned j = 0; j < TAP16; j++)
		{
			coef[j] = fir16e_p.coef[j];
		}

		for (unsigned j = 0; j < TAP16; j++)
		{
			shift[j] = fir16e_p.shift[j];
		}

		// process
		acc=sample_tmp*coef[0];

		for(int i=TAP16-2; i>=0; i--)
		{
			pro=shift[i]*coef[i+1];
			acc += pro;
		}

		// fill datatype
		fir16e_r.acc=acc;

		// send results by channel
		fir16e_results_channel->write(fir16e_r);
	}
}
