#pragma once

#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include <cmath>

#define AREA_TO_DISTANCE_MULTIPLIER 1 //THIS NUMBER REQUIRES CALIBRATION ONCE CIRCUIT BOARD IS RUNNING.
#define LIMELIGHT_SPEED 0.55//defaultl speed
#define LIMELIGHT_MAX_AREA 8 //13.5 is too close
#define LIMELIGHT_BALL_CORRECTION 12 //degrees correction for ball. Hatch shouldn't need corrections. 
#define LIMELIGHT_HATCH_CORRECTION -4

#define LIMELIGHT_TURNSPEED 0.5
#define LIMELIGHT_TOLERANCE 2
#define LIMELIGHT_HEIGHT 32.0
#define HATCH_VISION_STRIP_HEIGHT 29.0
#define BALL_VISION_STRIP_HEIGHT 38.0
#define LIMELIGHT_ANGLE 0.0



class CitrusLumen {
 
 public:
  CitrusLumen();

  bool targetLocated();

  double targetOffset_Vertical();
  double targetOffset_Horizontal();
  double targetSkew();
  double targetArea();
  double forwardSpeed();
  double horizontalBallSpeed();
  double horizontalHatchSpeed();
  double getBallCorrection();
  double getHatchCorrection();
  bool autonBallLimelight();
  bool autonHatchLimelight();

  double getBallDistance();
  double getHatchDistance();

  void toggleLimelight(bool onOff);
  
 private:
  std::shared_ptr<NetworkTable> table;
  double currentOffset;
  double ballCorrectionMultiplier = LIMELIGHT_BALL_CORRECTION / LIMELIGHT_MAX_AREA;
  double hatchCorrectionMultiplier = LIMELIGHT_HATCH_CORRECTION / LIMELIGHT_MAX_AREA;
  
};
