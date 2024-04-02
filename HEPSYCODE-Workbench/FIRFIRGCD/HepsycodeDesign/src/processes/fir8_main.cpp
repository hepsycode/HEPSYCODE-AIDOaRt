/*****************************************************************************/
#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//f8m
void mainsystem::fir8_main()
{
	// datatype for channels
	fir8e_parameters fir8e_p;
	fir8e_results fir8e_r;
	fir8s_parameters fir8s_p;
	fir8s_results fir8s_r;

	// local variables
	sc_uint<8>  sample_tmp;
	sc_uint<19> acc;
	sc_uint<9> coef[8];
	sc_uint<8> shift[8];

	// init
	coef[0] = 6;
	coef[1] = 4;
	coef[2] = 13;
	coef[3] = 8;
	coef[4] = 18;
	coef[5] = 41;
	coef[6] = 23;
	coef[7] = 154;
	coef[8] = 222;

	for (unsigned int i=0; i<TAP8; i++)
	{
		shift[i] = 0;
	}

	// main functionality

	while (1)
	{


		// Main input from channel
		sample_tmp = stim1_channel_port->read();

		//fir8e

		// fill datatype
		fir8e_p.acc = acc;

		for (unsigned j = 0; j < TAP8; j++)
		{

				fir8e_p.coef[j] = coef[j];

		}

		fir8e_p.sample_tmp = sample_tmp;

		for (unsigned j = 0; j < TAP8; j++)
		{

				fir8e_p.shift[j] = shift[j];

		}

		// send parameters and receive results
		fir8e_parameters_channel->write(fir8e_p);
		fir8e_r = fir8e_results_channel->read();

		// fill local variables
		acc = fir8e_r.acc;

		//fir8s

		// fill datatype
		fir8s_p.sample_tmp = sample_tmp;

		for (unsigned j = 0; j < TAP8; j++)
		{

				fir8s_p.shift[j] = shift[j];

		}

		// send parameters and receive results
		fir8s_parameters_channel->write(fir8s_p);
		fir8s_r = fir8s_results_channel->read();

		// fill local variables
		for( unsigned j=0; j<TAP8; j++)
		{
			shift[j] = fir8s_r.shift[j];
		}

		// write output values on channel
		results8_channel->write(acc);

		#if defined(_DEBUG_)
			cout << "FIR8: \t\t" << acc << "\t at time \t" << sc_time_stamp() << endl;
		#endif
	}
}
