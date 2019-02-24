#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot()
  : m_drivetrain(),
   m_driver(JOYSTICK_PORT),
   m_driver2(JOYSTICK2_PORT),
   m_lime(),
   m_intake(),
   m_elevator()
   {}

void Robot::consoleOut(std::string desc, double output){
  if (consoleOutputCounter==50){
  std::cout << desc << output << std::endl;
  consoleOutputCounter = 0;
  }
  else{
    consoleOutputCounter++;
  }
}

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //ultra = new frc::Ultrasonic(0,1);
  m_drivetrain.resetEncoders();

}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_drivetrain.resetEncoders();
  autonCase = 0;

  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic(){
  
  /* // Don't think we need this stuff. 
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
  */
  
  switch (autonCase){
    
    case 0:
		m_drivetrain.encoderWrite(8.0, 8.0);
    break;

    case 1:
    break;
		}
}

void Robot::TeleopInit() {
  m_drivetrain.resetEncoders();
}

void Robot::TeleopPeriodic() {
  //Robot::consoleOut("range2: ", m_elevator.getUltra2Inches());
  //Robot::consoleOut("range: ", m_elevator.getUltraInches());

  //Robot::consoleOut("Encoder distance: ", m_drivetrain.getDistance());
  //Robot::consoleOut("Arm Distance: ", m_intake.getDistance());
  Robot::consoleOut("Left Encoder distance: ", m_drivetrain.getLDistance());
  Robot::consoleOut("Right Encoder distance: ", m_drivetrain.getRDistance());
  //Robot::consoleOut("Limelight ta: ", m_lime.targetDistance());
  //Robot::consoleOut("Limelight target detected: ", m_lime.targetLocated());
  //Robot::consoleOut("Limelight Speed: ", m_lime.limelightSpeed());

  //   DRIVETRAIN   ///////////////////////////////////////
  if((m_lime.targetLocated()) && (m_driver.ButtonB())) {
   	m_drivetrain.ArcadeDrive(m_lime.limelightSpeed(), m_lime.horizontalSpeed() );
  }
  else if ((fabs (m_driver.AxisLY()) > 0.1 || fabs(m_driver.AxisRX())) > 0.1 ) {
		m_drivetrain.ArcadeDrive(-(SPEED_MULTIPLIER * (m_driver.AxisLY())), (SPEED_MULTIPLIER * (m_driver.AxisRX())));
  }
  else{
    m_drivetrain.ArcadeDrive(0.0,0.0);
  }
  //   ELEVATOR   ///////////////////////////////////////
  if(m_driver.ButtonA()) {
    m_elevator.setHeight(60.0);
  }
  else if(m_driver.ButtonLT()) {
     m_elevator.translateElevator(-ELEVATOR_SPEED);
  }
  else if(m_driver.ButtonLB()){
     m_elevator.translateElevator(ELEVATOR_SPEED);
  }
  else {
     m_elevator.translateElevator(0.06);
  }
  //   INTAKE   ///////////////////////////////////////
  if(m_driver.ButtonRT()) {
    m_intake.inOutBall(0.5);
  }
  else if(m_driver.ButtonRB()){
     m_intake.inOutBall(-0.5);
  }
  else {
     m_intake.inOutBall(0.0);
  }
  //   TILT   ///////////////////////////////////////
  if (m_driver.ButtonY()) {
    m_intake.inOutAngle(0.3);
   }
  else if ((m_driver.ButtonX())) {
    m_intake.inOutAngle(-0.3);
   }
  else{
    m_intake.inOutAngle(0.0);
  }
  /////////////////////////////////////////
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TEST
int main() { return frc::StartRobot<Robot>(); }
#endif
