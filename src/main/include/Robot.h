#pragma once

#include <string>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "Drivetrain.h"
#include "ProtoJoystick.h"
#include "CitrusLumen.h"
#include "Elevator.h"
#include "Intake.h"
#include <frc/IterativeRobotBase.h>

#include <frc/Timer.h>

#define JOYSTICK_PORT 0
#define JOYSTICK2_PORT 1
#define ELEVATOR_SPEED 0.75

#define HATCH_BOTTOM 24
#define HATCH_MIDDLE 51
#define HATCH_TOP 73
#define BALL_BOTTOM 34
#define BALL_MIDDLE 50//61
#define BALL_TOP 73

#define CARGO_SHIP 51

#define START_POSITION -1
#define ROCKET_OR_TRANSPORT 1
#define CENTER_TRANSPORT_RIGHTLEFT 1  //-1 = LEFT. 1 = RIGHT



class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  void consoleOut(std::string desc, double output);
  int consoleOutputCounter;  
  int autonCase;

  int hatchDisengageCase;
  //frc::Timer autonTimer;


 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  double speedMultiplier;
  bool autonAbort = false;
  
  Drivetrain m_drivetrain;
  ProtoJoystick m_driver;
  ProtoJoystick m_driver2;
  CitrusLumen m_lime;
  Elevator m_elevator;
  Intake m_intake;

  frc::Timer m_autonTimer;
};