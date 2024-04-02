/********************************************************************************
 * University of L'Aquila - HEPSYCODE Source Code License                       *
 *                                                                            	*
 *                                                                            	*
 * (c) 2018-2019 Centre of Excellence DEWS All rights reserved                	*
 ********************************************************************************
 * <one line to give the program's name and a brief idea of what it does.>      *
 * Copyright (C) 2022  Vittoriano Muttillo, Luigi Pomante                       *                                    *
 *                                                                              *
 * This program is free software: you can redistribute it and/or modify         *
 * it under the terms of the GNU General Public License as published by         *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU General Public License for more details.                                 *
 *                                                                              *
 ********************************************************************************
 *                                                                              *
 * Created on: 09/May/2022                                                      *
 * Authors: Vittoriano Muttillo, Luigi Pomante                                  *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        luigi.pomante@univaq.it                                               *
 *                                                                              *
 ********************************************************************************
 * This code has been developed from an HEPSYCODE model used as demonstrator by	*
 * University of L'Aquila.                                                      *
 *                                                                              *
 * The code is used as a working example in the 'Embedded Systems' course of    *
 * the Master in Conputer Science Engineering offered by the                    *
 * University of L'Aquila                                                       *
 *******************************************************************************/

/********************************************************************************
 * sc_csp_channel.h : The sc_csp_channel<T> primitive channel class.
 *
 * CSP Channel: Main SystemC HEPSIM2 csp channel header file
 *
********************************************************************************/

/*! \file sc_csp_channel.h
    \brief The sc_csp_channel<T> primitive channel class documented file.

    Details.
*/

/** @defgroup firfirgcd_csp_channel_group FirFirGCD CSP Channel.
 *
 *  CSP Channel Implementation
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_csp_channel_group

#ifndef SC_CSP_CHANNEL_H
#define SC_CSP_CHANNEL_H

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include "sysc/communication/sc_communication_ids.h"
#include "sysc/communication/sc_prim_channel.h"
#include "sysc/kernel/sc_event.h"
#include "sysc/communication/sc_communication_ids.h"
#include "sysc/kernel/sc_simcontext.h"
#include "sysc/tracing/sc_trace.h"
#include <typeinfo>

#include "sc_csp_channel_ifs.h"

#include "define.h"
#include "SystemManager.h"
#include "SchedulingManager.h"

extern SystemManager *pSystemManager;
extern SchedulingManager *pSchedulingManager;

using namespace sc_core;
using namespace std;

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

////////////////////////////
// SBM INDEPENDENT
////////////////////////////

// ----------------------------------------------------------------------------
//  CLASS : sc_csp_channel<T>
//
//  The sc_csp_channel<T> primitive channel class.
// ----------------------------------------------------------------------------

template <class T>
class sc_csp_channel
: public sc_csp_channel_in_if<T>,
  public sc_csp_channel_out_if<T>,
  public sc_prim_channel
{
	public:

	explicit sc_csp_channel(
						unsigned int channel_id=0
						):sc_prim_channel( sc_gen_unique_name( "csp_channel" ) ),
						  ready_to_read_event(sc_gen_unique_name( "read_event" )),
						  ready_to_write_event(sc_gen_unique_name("write_event" )),
						  ready_alt_event(sc_gen_unique_name("alt_event"))
					{
						id=channel_id;
						w_id= pSystemManager->VCH[id].getW_id();
						r_id= pSystemManager->VCH[id].getR_id();
						width= pSystemManager->VCH[id].getWidth();

						tcomm= pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getTcomm();
						tacomm= pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getTAcomm();
						physical_width= pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getPhysicalWidth();

						init();
					}


		// interface methods
	    virtual void register_port( sc_port_base&, const char* );

		// blocking read
		virtual void read( T& );
		virtual T read();
 
		// blocking write
		virtual void write( const T& );

		// ALT management
		virtual bool read_test();
		virtual bool write_test();
		virtual void register_alt();
		virtual const sc_event & get_alt_event();

		// other methods

		operator T ()
		{ return read(); }

		sc_csp_channel<T>& operator = ( const T& a )
		{ write( a ); return *this; }

		void trace( sc_trace_file* tf ) const;

		virtual const char* kind() const
		{ return "sc_csp_channel"; }

	protected:

		void init();

		sc_event ready_to_read_event;
		sc_event ready_to_write_event;
		sc_event ready_alt_event;

		bool ready_to_read;
		bool ready_to_write;
		bool enable_alt_events;

		T  csp_buf; // the buffer

	public:
		unsigned int id;
		unsigned int w_id; // writer ID
		unsigned int r_id; // reader ID
		unsigned int width; // #bytes for each logical transfer
		unsigned int num;  // #logical transfers
		bool IPC; // interprocessor communication

		sc_time waiting_time; // time for 1 communication over the channel
		sc_time working_time; // time for all the communications over the channel

		double partial_energy; // energy for 1 transmission over the channel
		double working_energy; // energy for all the transmissions over the channel

		sc_time tcomm; // time for 1 transmission over the physical link on which the channel has been allocated
		sc_time tacomm; // time for accessing the physical link on which the channel has been allocated
		unsigned int physical_width; // width of the physical link on which the channel has been allocated

	protected:
		sc_port_base* m_reader;	// used for static design rule checking
		sc_port_base* m_writer;	// used for static design rule checking

};

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

// register port

template <class T>
inline
void
sc_csp_channel<T>::register_port( sc_port_base& port_,
			    const char* if_typename_ )
{
    std::string nm( if_typename_ );
    if( nm == typeid( sc_csp_channel_in_if<T> ).name())
	{
		// only one reader can be connected
		if( m_reader != 0 ) {
			SC_REPORT_ERROR("sc_csp_channel<T> cannot have more than one reader", 0 );
	}
	m_reader = &port_;
    } else if( nm == typeid( sc_csp_channel_out_if<T> ).name()) {
		// only one writer can be connected
		if( m_writer != 0 ) {
			SC_REPORT_ERROR("sc_csp_channel<T> cannot have more than one writer", 0 );
		}
	m_writer = &port_;
    }
    else
    {
        SC_REPORT_ERROR( SC_ID_BIND_IF_TO_PORT_, 
	                 "sc_csp_channel<T> port not recognized" );
    }
}

// blocking read

template <class T>
inline
void
sc_csp_channel<T>::read( T& val_ )
{
	//	Update process status (also testbench processes)
	pSchedulingManager->process_state[r_id]=waiting;
	HEPSY_TRACE_PS_STATE(r_id)

	// Update channel status (if needed)
	if (pSchedulingManager->channel_state[id]==waiting)
	{
		pSchedulingManager->channel_state[id]=ready;
		HEPSY_TRACE_CH_STATE(id)
	}

	// Update BB mode (only for SPP, the others PUs are managed in the schedulers)
	if (pSystemManager->checkSPP(r_id)==true)
	{
		pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[r_id]]=suspended;
		HEPSY_TRACE_BB_STATE(r_id)
	}

	if(ready_to_write==true)
	{
		ready_to_read=true;
		ready_to_read_event.notify(SC_ZERO_TIME);
		sc_core::wait(ready_to_write_event);

		val_=csp_buf;

		ready_to_read=false;
		ready_to_read_event.notify(SC_ZERO_TIME);
	}
	else
	{
		ready_to_read=true;

		if (enable_alt_events) ready_alt_event.notify(SC_ZERO_TIME); // added for ALT
		sc_core::wait(ready_to_write_event);

		val_=csp_buf;

		ready_to_read=false;
		ready_to_read_event.notify(SC_ZERO_TIME);
		sc_core::wait(ready_to_write_event);
	}

	// Update BB mode
	if (pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[r_id]]==suspended)
	{
		if (pSystemManager->checkSPP(r_id)==true)
		{
			pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[r_id]]=active;
			HEPSY_TRACE_BB_STATE(r_id)
		}
		else pSchedulingManager->activate[pSystemManager->allocationPS_BB[r_id]].notify(SC_ZERO_TIME); // Ask to the scheduler to reactivate BB
	}

	// Update channel status (if needed)
	if (pSchedulingManager->channel_state[id]==ready)
	{
		pSchedulingManager->channel_state[id]=waiting;
		HEPSY_TRACE_CH_STATE(id)
	}

	//	Update process status (also testbench processes)
	if (pSystemManager->checkSPP(r_id)==true) pSchedulingManager->process_state[r_id]=running;
	else
	{
		pSchedulingManager->process_state[r_id]=ready;

		//WARNING: needed to correctly perform the round check (see WARNING in scheduler)
		pSchedulingManager->process_status_changed[pSystemManager->allocationPS_BB[r_id]]=true;
	}
	HEPSY_TRACE_PS_STATE(r_id)
}

template <class T>
inline
T
sc_csp_channel<T>::read()
{
    T tmp;
    read( tmp );
    return tmp;
}

// blocking write

template <class T>
inline
void
sc_csp_channel<T>::write( const T& val_ )
{
	//	Update process status (also testbench processes)
	pSchedulingManager->process_state[w_id]=waiting;
	HEPSY_TRACE_PS_STATE(w_id)

	// Update channel status (if needed)
	if (pSchedulingManager->channel_state[id]==waiting)
	{
		pSchedulingManager->channel_state[id]=ready;
		HEPSY_TRACE_CH_STATE(id)
	}

	// Update BB mode (only for SPP, the others PUs are managed in the schedulers)
	if (pSystemManager->checkSPP(w_id)==true)
	{
		pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[w_id]]=suspended;
		HEPSY_TRACE_BB_STATE(w_id)
	}

	if( ready_to_read==true)
	{
		csp_buf=val_;

		ready_to_write=true;
		ready_to_write_event.notify(SC_ZERO_TIME);
		sc_core::wait(ready_to_read_event);

		// Update channel status
		pSchedulingManager->channel_state[id]=running;
		HEPSY_TRACE_CH_STATE(id)

		// Manage simulated time and energy
		wait(waiting_time);
		working_time+= waiting_time;
		working_energy+=partial_energy;

		// Update channel status
		pSchedulingManager->channel_state[id]=ready;
		HEPSY_TRACE_CH_STATE(id)

		ready_to_write=false;
		ready_to_write_event.notify(SC_ZERO_TIME);
	}
	else
	{
		ready_to_write=true;

		if (enable_alt_events) ready_alt_event.notify(SC_ZERO_TIME); // added for ALT
		sc_core::wait(ready_to_read_event);

		csp_buf=val_;

		// Update channel status
		pSchedulingManager->channel_state[id]=running;
		HEPSY_TRACE_CH_STATE(id)

		// Manage simulated time and energy
		wait(waiting_time);
		working_time+= waiting_time;
		working_energy+=partial_energy;

		// Update channel status
		pSchedulingManager->channel_state[id]=ready;
		HEPSY_TRACE_CH_STATE(id)

		ready_to_write=false;
		ready_to_write_event.notify(SC_ZERO_TIME);
		sc_core::wait(ready_to_read_event);
	}										

	// Update BB mode
	if (pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[w_id]]==suspended)
	{
		if (pSystemManager->checkSPP(w_id)==true)
		{
			pSchedulingManager->BB_mode[pSystemManager->allocationPS_BB[w_id]]=active;
			HEPSY_TRACE_BB_STATE(w_id)
		}
		else
			pSchedulingManager->activate[pSystemManager->allocationPS_BB[w_id]].notify(SC_ZERO_TIME);
	}

	// Update channel status (if needed)
	if (pSchedulingManager->channel_state[id]==ready)
	{
		pSchedulingManager->channel_state[id]=waiting;
		HEPSY_TRACE_CH_STATE(id)
	}

	//	Update process status
	if (pSystemManager->checkSPP(w_id)==true) pSchedulingManager->process_state[w_id]=running;
	else
	{
		pSchedulingManager->process_state[w_id]=ready;

		//WARNING: needed to correctly perform the round check (see WARNING in scheduler)
		pSchedulingManager->process_status_changed[pSystemManager->allocationPS_BB[w_id]]=true;
	}
	HEPSY_TRACE_PS_STATE(w_id)

	// Channel profiling (done only in write metod)
	num++;
	pSystemManager->VCH[id].setNum(num);
	pSystemManager->VCH[id].working_time = working_time;
	pSystemManager->VCH[id].working_energy = working_energy;
}

template <class T>
inline
void
sc_csp_channel<T>::trace( sc_trace_file* tf ) const
{
	// WIP
}


template <class T>
inline
void
sc_csp_channel<T>::init()
{
    m_reader = 0;
    m_writer = 0;

	num=0;
	ready_to_read=false;
	ready_to_write=false;
	enable_alt_events = false;

	working_time = sc_time(0, SC_MS);
	working_energy=0;

	// verify if the processes are allocated on the same BB (then IPC=false)
	if ((w_id==stimulus_id) || (w_id==display_id) || (r_id==stimulus_id) || (r_id==display_id))
	{
		// Communications toward testbench are always considered
		IPC = true;
	}
	else if (pSystemManager->VBB[pSystemManager->allocationPS_BB[w_id]].getProcessors()[0].getName() !=
		pSystemManager->VBB[pSystemManager->allocationPS_BB[r_id]].getProcessors()[0].getName())
	{
		// Different BB names
		IPC = true;
	}
	else if (pSystemManager->VBB[pSystemManager->allocationPS_BB[w_id]].getId() !=
		pSystemManager->VBB[pSystemManager->allocationPS_BB[r_id]].getId())
	{
		// Different BB instances
		IPC = true;
	}
	else IPC=false;

	if (IPC==true)
	{

		// compute the time needed for the communication
		waiting_time = (ceil((float)width/pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getPhysicalWidth())*pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getTcomm()+pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getTAcomm());

		// LP: non mi torna la trasmissione seriale di pi� bit dato che ne consideriamo sempre solo uno alla volta (check tesi Marinella)
		// compute the energy needed for the communication 
		// energy for x bit is: a2 * x^2 + a1 * x
		// en_bit = energy for 1 bit = a2 + a1
		float en_bit =  pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].geta2() + pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].geta1();

		// energy for 1 transmission is: en_bit * PhysicalWidth
		float en_trans = en_bit * pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getPhysicalWidth();

		// energy for communication is: energy for 1 transmission * #transmissions
		partial_energy = ceil((float)width/pSystemManager->VPL[pSystemManager->allocationCH_PL[id]].getPhysicalWidth()) * en_trans;

	}
	else
	{

		// Zero for processes on the same BB/PU
		waiting_time = sc_time(0, SC_MS);

		// Zero for processes on the same BB/PU
		partial_energy = 0;

	}

}

//// ALT-support MANAGEMENT 

// read_test
template <class T>
inline
bool
sc_csp_channel<T>::read_test()
{
	return ready_to_write;
}

// write_test
template <class T>
inline
bool
sc_csp_channel<T>::write_test()
{
	return ready_to_read;
}

// enable ALT
template <class T>
inline
void
sc_csp_channel<T>::register_alt()
{
	enable_alt_events = true;
}

// get ALT event
template <class T>
inline
const sc_event &
sc_csp_channel<T>::get_alt_event()
{
	return ready_alt_event;
}

/** @} */ // end of firfirgcd_csp_channel_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
