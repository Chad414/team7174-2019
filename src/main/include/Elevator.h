#pragma once

#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/Talon.h>
#include <frc/Encoder.h>
#include <frc/Ultrasonic.h>

#define ELEVATOR_TALON 0

class Elevator {
 public:

  Elevator();

  void translateElevator(double speed);
  double getUltraInches();
  void setHeight(double height);

private:

  WPI_TalonSRX  Lift;
  frc::Ultrasonic *ultra;

};
