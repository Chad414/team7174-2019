/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

#define AREA_TO_DISTANCE_MULTIPLIER 1 //THIS NUMBER REQUIRES CALIBRATION ONCE CIRCUIT BOARD IS RUNNING.
#define LIMELIGHT_SPEED 0.5
#define LIMELIGHT_MIN_DISTANCE 80
#define LIMELIGHT_TURNSPEED 0.5


class CitrusLumen {
 
 public:
  CitrusLumen();

  bool targetLocated();

  double targetOffset_Vertical();
  double targetOffset_Horizontal();
  double targetSkew();
  double targetArea();
  double targetDistance();
  double limelightSpeed();
  double horizontalSpeed();
  
 private:
  std::shared_ptr<NetworkTable> table;
 
  
};
