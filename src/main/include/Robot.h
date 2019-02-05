/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "Drivetrain.h"
#include "ProtoJoystick.h"
#include "CitrusLumen.h"
#include "Elevator.h"

#define JOYSTICK_PORT 0
#define SPEED_MULTIPLIER 1.0
#define LIMELIGHT_ANGLE 0.037 // == 1/27
#define LIMELIGHT_MAX_DISTANCE 500
#define ELEVATOR_SPEED 1.0

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

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;


  Drivetrain m_drivetrain;
  ProtoJoystick m_driver;
  CitrusLumen m_lime;
  Elevator m_elevator;
};
//w