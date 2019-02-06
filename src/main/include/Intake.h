#pragma once

#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/Talon.h>
#include <frc/Encoder.h>

#define BALL_OBTAINER_TALON 0
#define BALL_ANGLE_TALON 0

class Intake {
 public:

  Intake();

  void inOutBall(double speed);
  void inOutAngle(double speed);

private:

  WPI_TalonSRX  BallObtainer;
  WPI_TalonSRX  BallAngle;

};
