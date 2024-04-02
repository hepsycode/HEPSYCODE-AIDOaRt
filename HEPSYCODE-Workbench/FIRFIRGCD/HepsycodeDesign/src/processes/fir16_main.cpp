/*****************************************************************************/

#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//f16m
void mainsystem::fir16_main()
{
	// datatype for channels
	fir16e_parameters fir16e_p;
	fir16e_results fir16e_r;
	fir16s_parameters fir16s_p;
	fir16s_results fir16s_r;

	// local variables
	sc_uint<8>  sample_tmp;
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8> shift[16];

	// init
	coef[0] = 6;
	coef[1] = 4;
	coef[2] = 13;
	coef[3] = 16;
	coef[4] = 18;
	coef[5] = 41;
	coef[6] = 23;
	coef[7] = 154;
	coef[8] = 222;
	coef[9] = 154;
	coef[10] = 23;
	coef[11] = 41;
	coef[12] = 18;
	coef[13] = 16;
	coef[14] = 13;
	coef[15] = 4;

	for (unsigned int i=0; i<TAP16; i++)
	{
		shift[i] = 0;
	}

	// main functionality

	while(1)
	{

		// Main input from channel
		sample_tmp=stim2_channel_port->read();
		
		//fir16e

		// fill datatype
		fir16e_p.acc=acc;

		for (unsigned j = 0; j < TAP16; j++)
		{
			fir16e_p.coef[j] = coef[j];
		}

		fir16e_p.sample_tmp=sample_tmp;

		for (unsigned j = 0; j < TAP16; j++)
		{
			fir16e_p.shift[j] = shift[j];
		}

		// send parameters and receive results
		fir16e_parameters_channel->write(fir16e_p);
		fir16e_r=fir16e_results_channel->read();

		// fill local variables
		acc=fir16e_r.acc;

		//fir16s

		// fill datatype
		fir16s_p.sample_tmp=sample_tmp;

		for (unsigned j = 0; j < TAP16; j++)
		{
			fir16s_p.shift[j] = shift[j];
		}

		// send parameters and receive results
		fir16s_parameters_channel->write(fir16s_p);
		fir16s_r=fir16s_results_channel->read();

		// fill local variables
		for (unsigned j = 0; j < TAP16; j++)
		{
			shift[j] = fir16s_r.shift[j];
		}

		// write output values on channel
		results16_channel->write(acc);
		
		#if defined(_DEBUG_)
		cout << "FIR16: \t\t" << acc << "\t at time \t" << sc_time_stamp() << endl;
		#endif
	}
}
