#pragma once

#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/Talon.h>
#include <frc/Encoder.h>

#define ELEVATOR_TALON 0

class Elevator {
 public:

  Elevator();

  void translateElevator(double speed);

private:

  WPI_TalonSRX  Lift;

};
