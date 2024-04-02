/*****************************************************************************/

#include "../mainsystem.h"

////////////////////////////
// SBM DEPENDENT
////////////////////////////

//gcdm
void mainsystem::gcd_main()
{

	// datatype for channels
	gcde_parameters gcde_p;
	gcde_results gcde_r;

	// local variables
	sc_uint<8> sample1;
	sc_uint<8> sample2;
	sc_uint<8> result;
	bool err;

	// init
	err=false;

	while(1)
	{
		// main functionality

		// Main input from channel

		sample1=results8_channel->read();
		if (sample1==0) err=true;

		sample2=results16_channel->read();
		if (sample2==0) err=true;

		//cout<<"sample1: "<<sample1_tmp<<" sample2: "<<sample2_tmp<<endl;

		if (err==false)
		{
			// fill datatype
			gcde_p.sample1=sample1;
			gcde_p.sample2=sample2;

			// send parameters and receive results
			gcde_parameters_channel->write(gcde_p);
			gcde_r=gcde_results_channel->read();

			// fill local variables
			result=gcde_r.result;
		}
		else
		{
			result=0;
			err=false;
		}

		result_channel_port->write(result);

		#if defined(_DEBUG_)
			cout << "GCD: \t\t" << result << "\t at time \t" << sc_time_stamp() << endl;
		#endif
	}
}
