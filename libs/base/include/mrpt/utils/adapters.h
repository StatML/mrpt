/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                       http://www.mrpt.org/                                |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */
#ifndef mrpt_utils_adapters_H
#define mrpt_utils_adapters_H

#include <mrpt/utils/utils_defs.h>

namespace mrpt
{
	namespace utils
	{
		/** \defgroup mrpt_adapters_grp Adapter (wrapper) template classes
			\addtogroup mrpt_base_grp
		*/
		
		/** \addtogroup mrpt_adapters_grp
		  * @{ */

		/** An adapter to different kinds of point cloud object. 
		  *  Implemented as a pure C++ template with specializations for the highest flexibility and efficiency in compiler-generated implementations.
		  *  Usage:
		  *   \code
		  *     PC  my_obj; 
		  *     my_obj.specific_methods();
		  *     // ...
		  *     PointCloudAdapter<PC> pca(my_obj);
		  *     pca.unified_interface_methods(); 
		  *     // ...
		  *   \endcode
		  *  See specializations for details on the exposed API.
		  */
		template <class POINTCLOUD> class PointCloudAdapter;

		/** @} */  // end of grouping

	} // End of namespace
} // end of namespace
#endif
