/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <cmath>
#include <frc/Joystick.h>

class ProtoJoystick : public frc::Joystick {
 public:
typedef enum {
	kAxisLX = 1 << 0,
	kAxisLY = 1 << 1,
	kAxisLT = 1 << 2,	
	kAxisRT = 1 << 3,	
	kAxisRX = 1 << 4,
	kAxisRY = 1 << 5,
	kAxisALL = 0xFF
	} kAxis;

  ProtoJoystick(unsigned int port);

  float Axis(kAxis axis);


  float AxisLX() { return Axis(kAxisLX); }
	float AxisLY() { return Axis(kAxisLY); }
	float AxisRX() { return Axis(kAxisRX); }
	float AxisRY() { return Axis(kAxisRY); }
	float AxisLT() { return Axis(kAxisLT); }
	float AxisRT() { return Axis(kAxisRT); }
};
