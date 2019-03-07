#pragma once

#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/Talon.h>
#include <frc/Ultrasonic.h>
#include <frc/SerialPort.h>
#include <frc/I2C.h>

#define ELEVATOR_TALON 0
#define TOLERANCE_INCHES 1.5
#define VOLTAGE_MULTIPLIER 40.2969294

class Elevator {
 public:

  Elevator();

  void translateElevator(double speed);
  bool autonElevator(double height);
  
  double getLazerInches();

  void setHeight(double height);

private:

  uint8_t buffer;

  WPI_TalonSRX Lift;
  //frc::Ultrasonic ultra;
  //frc::Ultrasonic *ultra;
  
  //frc::AnalogInput *ai;

  frc::I2C lazer;
  double currentHeight=0;
  int upDown = 0;

};
