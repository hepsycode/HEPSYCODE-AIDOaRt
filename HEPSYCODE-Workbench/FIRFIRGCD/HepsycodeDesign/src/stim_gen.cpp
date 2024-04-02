#include "stim_gen.h"

////////////////////////////

// STIMULUS: GENERATES INPUTS FOR THE SYSTEM

////////////////////////////

extern bool stop_concurrency_sampling;

// Stimulus for stim1
void stim_gen::stimulus1()
{
	sc_uint<8> value1=1;
	sc_uint<8> value2=1;
	unsigned int i=1;
	sc_time setup(10, SC_MS), loop(10, SC_MS), expected(0, SC_MS);

	// Wait for setup
	wait(setup);
	expected += setup;

	while(i <= NUMBER_OF_INPUTS)
	{
		// Sends out value1
		wait(loop);
		expected += loop;
		stim1_channel_port->write(value1);
		cout << "Stimulus1-" << i << ": \t" << value1 << "\t at time \t" << sc_time_stamp() << " (" << sc_time_stamp().to_seconds() << "/" << expected.to_seconds() << ")" << endl;

		// Change next out values
		value1=value1+value2;
		value2=(value2*value1)+1;

		// Counter
		i++;
	}
	
	// Used to stop concurrency sampling (to allow the simulation to finish), if needed
		stop_sampling1 = true;
		if (stop_sampling2==true)
			// Stop sampling SC_THREAD in SchedulingManager
			stop_concurrency_sampling = true;
}

// Stimulus for stim2
void stim_gen::stimulus2()
{
	sc_uint<8> value1=1;
	sc_uint<8> value2=1;
	unsigned int i=1;
	sc_time setup(10, SC_MS), loop(10, SC_MS), expected(0, SC_MS);

	// Wait for setup
	wait(setup);
	expected += setup;

	while (i <= NUMBER_OF_INPUTS)
	{
		// Sends out value2
		wait(loop);
		expected += loop;
		stim2_channel_port->write(value2);
		cout << "Stimulus2-" << i << ": \t" << value1 << "\t at time \t" << sc_time_stamp() << " (" << sc_time_stamp().to_seconds() << "/" << expected.to_seconds() << ")" << endl;

		// Change next out values
		value1=value1+value2;
		value2=(value2*value1)+1;

		// Counter
		i++;
	}

	// Used to stop concurrency sampling (to allow the simulation to finish), if needed
		stop_sampling2 = true;
		if (stop_sampling1==true)
			// Stop sampling SC_THREAD in SchedulingManager
			stop_concurrency_sampling = true;
}

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
