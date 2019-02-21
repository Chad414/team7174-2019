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
#include <cmath>

#define AREA_TO_DISTANCE_MULTIPLIER 1 //THIS NUMBER REQUIRES CALIBRATION ONCE CIRCUIT BOARD IS RUNNING.
#define LIMELIGHT_SPEED 0.5
#define LIMELIGHT_MAX_AREA 8 //13.5 is too close
#define LIMELIGHT_MAX_CORRECTION 12

#define LIMELIGHT_TURNSPEED 0.5
#define LIMELIGHT_TOLERANCE 2


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
  double getLimelightCorrection();
  
 private:
  std::shared_ptr<NetworkTable> table;
  double currentOffset;
  double limelightCorrectionMultiplier = LIMELIGHT_MAX_CORRECTION / LIMELIGHT_MAX_AREA;
  
};
