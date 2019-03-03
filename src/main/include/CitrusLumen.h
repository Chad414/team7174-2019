#pragma once

#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include <cmath>

#define AREA_TO_DISTANCE_MULTIPLIER 1 //THIS NUMBER REQUIRES CALIBRATION ONCE CIRCUIT BOARD IS RUNNING.
#define LIMELIGHT_SPEED 0.55//defaultl speed
#define LIMELIGHT_MAX_AREA 8 //13.5 is too close
#define LIMELIGHT_MAX_CORRECTION 12 //degrees correction for ball. Hatch shouldn't need corrections. 

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
