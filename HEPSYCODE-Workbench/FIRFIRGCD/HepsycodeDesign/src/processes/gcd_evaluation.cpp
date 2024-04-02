
#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//gcde
void mainsystem::gcd_evaluation()
{
	// datatype for channels
	gcde_parameters gcde_p;
	gcde_results gcde_r;

	// local variables
	sc_uint<8>  sample1;
	sc_uint<8>  sample2;

	while(1)
	{

		// read parameters from channel
		gcde_p=gcde_parameters_channel->read();

		// fill local variables
		sample1=gcde_p.sample1;
		sample2=gcde_p.sample2;

		while(sample1!=sample2)
		{

			if (sample1>sample2) //HEPSY_S rules: IF like WHILE
			{
				sample1=sample1-sample2;
			}
			else //HEPSY_S rules: ELSE like WHILE
			{
				sample2= sample2-sample1;
			}

		}

		// fill datatype
		gcde_r.result=sample1;

		// send results to channel
		gcde_results_channel->write(gcde_r);
	}
}
