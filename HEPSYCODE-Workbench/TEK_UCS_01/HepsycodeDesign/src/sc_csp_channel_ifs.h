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
 * Created on: 09/May/2023                                                      *
 * Authors: Vittoriano Muttillo, Marco Santic, Luigi Pomante                    *
 *                                                                              *
 * email: vittoriano.muttillo@guest.univaq.it                                   *
 *        marco.santic@guest.univaq.it                                          *
 *        luigi.pomante@univaq.it                                               *
 *                                                                              *
 ********************************************************************************
 * This code has been developed from an HEPSYCODE model used as demonstrator by	*
 * University of L'Aquila.                                                      *
 *******************************************************************************/

/*****************************************************************************

  sc_csp_ifs.h -- The sc_csp_channel<T> interface classes.

 *****************************************************************************/

#ifndef __SC_CSPCHANNEL_IFS_H__
#define __SC_CSPCHANNEL_IFS_H__

#include "sysc/communication/sc_interface.h"

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

#endif
