/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#pragma once

#include <mrpt/math/lightweight_geom_data.h>
#include <mrpt/nav/link_pragmas.h>

namespace mrpt
{
	namespace nav
	{
		/** @addtogroup  nav_geom_grp Motion planning geometry utility functions (`#include <mrpt/nav/nav_plan_geometry_utils.h>`)
		*  \ingroup mrpt_nav_grp
		* @{ */

		/** Computes the collision-free distance for a linear segment path between two points, for a circular robot, and a point obstacle (ox,oy). 
		  * \return true if a collision exists, and the distance along the segment will be in out_col_dist; false otherwise;
		  * \exception std::runtime_error If the two points are closer than an epsilon (1e-10)
		  */
		bool NAV_IMPEXP collision_free_dist_segment_circ_robot(const mrpt::math::TPoint2D &p_start, const mrpt::math::TPoint2D &p_end, const double robot_radius, const mrpt::math::TPoint2D &obstacle, double &out_col_dist );

	  /** @} */
	}
}