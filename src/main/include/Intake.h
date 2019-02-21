#pragma once

#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/Talon.h>
#include <frc/Encoder.h>
#include <frc/Victor.h>

#define RBALL_OBTAINER_VICTOR 6
#define LBALL_OBTAINER_VICTOR 7
#define BALL_ANGLE_TALON 5

#define ANGLE_ENCODER 0

class Intake {
 public:
  Intake();
  void inOutBall(double speed);
  void inOutAngle(double speed);
  double getDistance();

private:

  WPI_VictorSPX  LBallObtainer;
  WPI_VictorSPX  RBallObtainer;
  WPI_TalonSRX  BallAngle;

  //frc::Encoder angleEncoder;
  

};
