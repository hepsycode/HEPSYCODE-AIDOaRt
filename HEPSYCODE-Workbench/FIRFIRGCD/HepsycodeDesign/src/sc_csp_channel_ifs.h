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
 * sc_csp_channel_ifs.h : The sc_csp_channel<T> interface classes.
 *
 * CSP Channel: Main SystemC HEPSIM2 csp channel interface header file
 *
********************************************************************************/

/*! \file sc_csp_channel_ifs.h
    \brief The sc_csp_channel<T> interface classes documented file.

    Details.
*/

/** @defgroup firfirgcd_csp_channel_ifs_group FirFirGCD CSP Channel Interfaces.
 *
 *  CSP Channel Interfaces
 *
 *  @author V. Muttillo, L. Pomante
 *  @date Apr. 2022
 *  @{
 */ // start firfirgcd_csp_channel_ifs_group

#ifndef __SC_CSPCHANNEL_IFS_H__
#define __SC_CSPCHANNEL_IFS_H__

/********************************************************************************
 ***                                Includes                                  ***
 *******************************************************************************/

#include "sysc/communication/sc_interface.h"

/********************************************************************************
 ***                                Functions                                 ***
 *******************************************************************************/

namespace sc_core
{

 // ----------------------------------------------------------------------------
 //  CLASS : sc_csp_channel_in_if<T>
 //
 //  The sc_csp_channel<T> input interface class.
 // ----------------------------------------------------------------------------

 template <class T> 
 class sc_csp_channel_in_if 
 :virtual public sc_interface 
 { 
	public: 

		// blocking read 
		virtual void read( T& ) = 0; 
		virtual T read() = 0; 

		// ALT-support management
		virtual bool read_test() = 0;
		virtual void register_alt() = 0;
		virtual const sc_event & get_alt_event() = 0;

 protected: 

		// constructor 
		sc_csp_channel_in_if() {} 

}; 

 // ----------------------------------------------------------------------------
 //  CLASS : sc_csp_channel_out_if<T>
 //
 //  The sc_csp_channel<T> output interface class.
 // ----------------------------------------------------------------------------

 template <class T> 
 class sc_csp_channel_out_if 
 :virtual public sc_interface 
 { 
	public: 

	    // blocking write 
		virtual void write( const T& ) = 0; 

		// ALT-support management
		virtual bool write_test() = 0;
		virtual void register_alt() = 0;
		virtual const sc_event & get_alt_event() = 0;

	protected: 

	    // constructor 
		sc_csp_channel_out_if(){} 

}; 

} //end of namespace

/** @} */ // end of firfirgcd_csp_channel_ifs_group

#endif

/********************************************************************************
 ***                                  EOF                                     ***
 ********************************************************************************/
