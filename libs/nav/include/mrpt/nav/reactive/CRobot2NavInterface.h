/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */
#pragma once

#include <mrpt/math/lightweight_geom_data.h>
#include <mrpt/nav/link_pragmas.h>
#include <mrpt/obs/obs_frwds.h> // CSimplePointsMap
#include <mrpt/utils/CTicTac.h>
#include <mrpt/system/datetime.h>
#include <mrpt/kinematics/CVehicleVelCmd.h>

namespace mrpt
{
  namespace nav
  {
	/** The pure virtual interface between a real or simulated robot and any `CAbstractNavigator`-derived class.
	  *
	  *  The user must define a new class derived from `CRobot2NavInterface` and reimplement
	  *   all pure virtual and the desired virtual methods according to the documentation in this class.
	  * 
	  * [New in MRPT 1.5.0] This class does not make assumptions about the kinematic model of the robot, so it can work with either 
	  *  Ackermann, differential-driven or holonomic robots. It will depend on the used PTGs, so checkout 
	  *  each PTG documentation for the lenght and meaning of velocity commands.
	  *
	  * If used for a simulator, users may prefer to inherit from one of these classes, which already provide partial implementations:
	  *  - mrpt::nav::CRobot2NavInterfaceForSimulator_DiffDriven
	  *  - mrpt::nav::CRobot2NavInterfaceForSimulator_Holo
	  *
	  * \sa CReactiveNavigationSystem, CAbstractNavigator
	  *  \ingroup nav_reactive
	  */
	class NAV_IMPEXP CRobot2NavInterface
	{
	public:
		CRobot2NavInterface();
		virtual ~CRobot2NavInterface();

		/** Get the current pose and speeds of the robot. The implementation should not take too much time to return,
		*   so if it might take more than ~10ms to ask the robot for the instantaneous data, it may be good enough to
		*   return the latest values from a cache which is updated in a parallel thread.
		*
		* \param[out] curPose The latest robot pose, in world coordinates. (x,y: meters, phi: radians)
		* \param[out] curVelGlobal  The latest robot velocity vector, in world coordinates. (vx,vy: m/s, omega: rad/s)
		* \param[out] timestamp  The timestamp for the read pose and velocity values. Use mrpt::system::now() unless you have something more accurate.
		* \return false on any error retrieving these values from the robot.
		*/
		virtual bool getCurrentPoseAndSpeeds(mrpt::math::TPose2D &curPose, mrpt::math::TTwist2D &curVelGlobal, mrpt::system::TTimeStamp &timestamp ) = 0;

		/** Sends a velocity command to the robot.
		 * The number components in each command depends on children classes of mrpt::kinematics::CVehicleVelCmd.
		 * One robot may accept one or more different CVehicleVelCmd classes.
		 * This method resets the watchdog timer (that may be or may be not implemented in a particular robotic platform) started with startWatchdog()
		 * \return false on any error.
		 * \sa startWatchdog
		 */
		virtual bool changeSpeeds(const mrpt::kinematics::CVehicleVelCmd &vel_cmd) = 0;

		/** Just like changeSpeeds(), but will be called when the last velocity command is still the preferred solution, 
		  * so there is no need to change that past command. The unique effect of this callback would be resetting the watchdog timer. 
		  * \return false on any error.
		  * \sa changeSpeeds(), startWatchdog() */
		virtual bool changeSpeedsNOP();

		/** Stop the robot right now. 
		 *  \param[in] isEmergencyStop true if stop is due to some unexpected error. false if "stop" happens as part of a normal operation (e.g. target reached).
		 * \return false on any error.
		 */
		virtual bool stop(bool isEmergencyStop=true) = 0;

		/** Gets the emergency stop command for the current robot
		  * \return the emergency stop command
		  */
		virtual mrpt::kinematics::CVehicleVelCmdPtr getEmergencyStopCmd() = 0;

		/** Gets the emergency stop command for the current robot
		  * \return the emergency stop command
		  */
		virtual mrpt::kinematics::CVehicleVelCmdPtr getStopCmd() = 0;

		/** Gets a motion command to make the robot to align with a given *relative* heading, without translating.
		  * Only for circular robots that can rotate in place; otherwise, return an empty smart pointer to indicate 
		  * that the operation is not possible (this is what the default implementation does). */
		virtual mrpt::kinematics::CVehicleVelCmdPtr getAlignCmd(const double relative_heading_radians);

		/** Start the watchdog timer of the robot platform, if any, for maximum expected delay between consecutive calls to changeSpeeds().
		 * \param T_ms Period, in ms.
		 * \return false on any error. */
		virtual bool startWatchdog(float T_ms);

		/** Stop the watchdog timer.
		 * \return false on any error. \sa startWatchdog */
		virtual bool stopWatchdog();

		/** Return the current set of obstacle points, as seen from the local coordinate frame of the robot.
		  * \return false on any error.
		  * \param[out] obstacles  A representation of obstacles in robot-centric coordinates.
		  * \param[out] timestamp  The timestamp for the read obstacles. Use mrpt::system::now() unless you have something more accurate.
		  */
		virtual bool senseObstacles( mrpt::maps::CSimplePointsMap &obstacles, mrpt::system::TTimeStamp &timestamp) = 0;

		/** Callback: Start of navigation command */
		virtual void sendNavigationStartEvent();
		
		/** Callback: End of navigation command (reach of single goal, or final waypoint of waypoint list) */
		virtual void sendNavigationEndEvent();

		/** Callback: Reached an intermediary waypoint in waypoint list navigation.
		  * reached_nSkipped will be `true` if the waypoint was physically reached; `false` if it was actually "skipped".
		  */
		virtual void sendWaypointReachedEvent(int waypoint_index, bool reached_nSkipped);

		/** Callback: Heading towards a new intermediary/final waypoint in waypoint list navigation */
		virtual void sendNewWaypointTargetEvent(int waypoint_index);

		/** Callback: Error asking sensory data from robot or sending motor commands. */
		virtual void sendNavigationEndDueToErrorEvent();

		/** Callback: No progression made towards target for a predefined period of time. */
		virtual void sendWaySeemsBlockedEvent();

		/** Returns the number of seconds ellapsed since the constructor of this class was invoked, or since 
		  * the last call of resetNavigationTimer(). This will be normally wall-clock time, except in simulators where this method will return simulation time. */
		virtual double getNavigationTime();
		/** see getNavigationTime() */
		virtual void resetNavigationTimer();

	private:
		mrpt::utils::CTicTac  m_navtime; //!< For getNavigationTime
	};

  }
}

