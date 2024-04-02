
#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//f8e
void mainsystem::fir8_evaluation()
{
	// datatype for channels
	fir8e_parameters fir8e_p;
	fir8e_results fir8e_r;

	// local variables
	sc_int<17> pro;
	sc_uint<19> acc;
	sc_uint<9> coef[8];
	sc_uint<8>  sample_tmp;
	sc_uint<8> shift[8];

	while(1) //HEPSY_S rules for WHILE: before while, and after {
	{

		// read parameters from channel
		fir8e_p=fir8e_parameters_channel->read();

		// fill local variables
		sample_tmp=fir8e_p.sample_tmp;

		for (unsigned j = 0; j < TAP8; j++)
		{
			coef[j] = fir8e_p.coef[j];
		}

		for (unsigned j = 0; j < TAP8; j++)
		{
				shift[j] = fir8e_p.shift[j];
		}

		// process
		acc=sample_tmp*coef[0];

		for(int i=TAP8-2; i>=0; i--) //HEPSY_S rules for FOR: before for, after {, and first of }
		{
			pro=shift[i]*coef[i+1];
			acc += pro;
		}

		// fill datatype
		fir8e_r.acc=acc;

		// send results by channel
		fir8e_results_channel->write(fir8e_r);
	}
}
