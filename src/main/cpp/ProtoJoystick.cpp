/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ProtoJoystick.h"

ProtoJoystick::ProtoJoystick(unsigned int port) 
: Joystick(port)
{}

float ProtoJoystick::Axis(kAxis axis) {
 switch(axis) {
	case kAxisLX:
		return fabs(GetRawAxis(0));
		break;
	case kAxisLY:
		return fabs(GetRawAxis(1));
		break;
	case kAxisLT:
		return fabs(GetRawAxis(2));
		break;
	case kAxisRT:
		return fabs(GetRawAxis(3));
		break;
	case kAxisRX:
		return fabs(GetRawAxis(4));
		break;
	case kAxisRY:
		return fabs(GetRawAxis(5));
		break;
	default:
		return 0.0;
}
}
