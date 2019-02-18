#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot()
  : m_drivetrain(),
   m_driver(JOYSTICK_PORT),
   m_lime(),
   m_intake(),
   m_elevator()
   
   {}

int consoleOutputCounter;
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
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
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

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}
  
void Robot::TeleopPeriodic() {

Robot::consoleOut("range: ", m_elevator.getUltraInches());
  //std::cout << "Distance: " << m_drivetrain.getDistance() << std::endl;
  //std::cout << "Limelight ta: " << m_lime.targetDistance() << std::endl;
  //std::cout<<"Limelight detected:" << m_lime.targetLocated() << std::endl;
  //std::cout << "Limelight Speed: " << m_lime.limelightSpeed() << std::endl;
  

///////////////////////////////////////
  if((m_lime.targetLocated()) && (m_driver.ButtonB())) {
    consoleOut("limelight running: ", 1);
   	m_drivetrain.ArcadeDrive(m_lime.limelightSpeed(), m_lime.horizontalSpeed() );
  }
/////////////////////////////////////////
  if ((fabs (m_driver.AxisLY()) > 0.1 || fabs(m_driver.AxisRX())) > 0.1 ) {

		m_drivetrain.ArcadeDrive(-(SPEED_MULTIPLIER * (m_driver.AxisLY())), (SPEED_MULTIPLIER * (m_driver.AxisRX())));
  }
//////////////////////////////////////////////////////////
  if(m_driver.ButtonLT()) {
     m_elevator.translateElevator(-ELEVATOR_SPEED);
  }
  else if(m_driver.ButtonLB()){
     m_elevator.translateElevator(ELEVATOR_SPEED);
  }
  else {
     m_elevator.translateElevator(0.06);
  }
  //////////////////////////////////////////
  if(m_driver.ButtonA()) {
    m_elevator.setHeight(12.0);
  }
///////////////////////////////////////
  if(m_driver.ButtonRT()) {
    m_intake.inOutBall(0.5);
  }
  else if(m_driver.ButtonRB()){
     m_intake.inOutBall(-0.5);
  }
  else {
     m_intake.inOutBall(0.0);
  }
/////////////////////////////////////////
  if (m_driver.ButtonY()) {
    m_intake.inOutAngle(0.2);
    std::cout<<"button y"<<std::endl;
  }
  
  else if ((m_driver.ButtonX())) {
    m_intake.inOutAngle(-0.2);
    std::cout<<"button x"<<std::endl;
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
