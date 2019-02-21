#pragma once

#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/Talon.h>
#include <frc/Ultrasonic.h>
//#include <frc/DigitalInput.h>

#define ELEVATOR_TALON 0
#define TOLERANCE_INCHES 0.25
#define VOLTAGE_MULTIPLIER 40.2969294

class Elevator {
 public:

  Elevator();

  void translateElevator(double speed);
  
  double getUltraInches();
  //double getUltra2Inches();

  void setHeight(double height);

private:

  WPI_TalonSRX Lift;
  //frc::Ultrasonic ultra;
  frc::Ultrasonic *ultra;
  
  //frc::AnalogInput *ai;


  double currentHeight=0;

};
