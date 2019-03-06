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
  //m_drivetrain.resetEncoders();
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_drivetrain.resetEncoders();
  m_intake.resetEncoders();
  autonCase = 0;

}

void Robot::AutonomousPeriodic(){
  
  
  switch (autonCase){
    case 0:
    if (m_drivetrain.autonDrivetrain(0.5, 0.5, 3.0, 3.0)){
      autonCase++;
    }
		break;
  }
}

void Robot::TeleopInit() {
  m_drivetrain.resetEncoders();
  m_intake.resetEncoders();
  speedMultiplier = 1.0;
}

void Robot::TeleopPeriodic() {
  //Robot::consoleOut("range2: ", m_elevator.getUltra2Inches());
  //Robot::consoleOut("range: ", m_elevator.getUltraInches());

  
  Robot::consoleOut("Angle encoder counts: ", m_intake.getDistance());
  //Robot::consoleOut("Angle Velocity: ", m_intake.getAngleVelocity());
  //Robot::consoleOut("angleEncoder2: ", m_intake.getEncoder2Distance());

  //Robot::consoleOut("Encoder distance: ", m_drivetrain.getDistance());
  //Robot::consoleOut("Left Encoder distance: ", m_drivetrain.getLDistance());
  //Robot::consoleOut("Right Encoder distance: ", m_drivetrain.getRDistance());
  
  //Robot::consoleOut("Lime light ta: ", m_lime.targetDistance());
  //Robot::consoleOut("Limelight target detected: ", m_lime.targetLocated());
  //Robot::consoleOut("Limelight Speed: ", m_lime.limelightSpeed());


  //   DRIVETRAIN   ///////////////////////////////////////
  if((m_lime.targetLocated()) && (m_driver.ButtonB())) {
   	m_drivetrain.ArcadeDrive(m_lime.forwardSpeed(), m_lime.horizontalBallSpeed() );
  }
  else if((m_lime.targetLocated()) && (m_driver.ButtonA())) {
   	m_drivetrain.ArcadeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed() );
  }
  else if((fabs (m_driver.AxisLY()) > 0.1 || fabs(m_driver.AxisRX())) > 0.1 ) {
		m_drivetrain.ArcadeDrive(-(speedMultiplier * (m_driver.AxisLY())), (speedMultiplier * (m_driver.AxisRX())));
  }
  else{
    m_drivetrain.ArcadeDrive(0.0,0.0);
  }

  if (m_driver.ButtonX()) {
    speedMultiplier = 0.5;
  }
  else if (m_driver.ButtonY()) {
    speedMultiplier = 1.0;
  }
  else{}
  //   ELEVATOR   ///////////////////////////////////////
  if(m_driver2.ButtonY() && m_driver2.ButtonLT()) {//cargos
    m_elevator.setHeight(65.0);
  }
  else if(m_driver2.ButtonX() && m_driver2.ButtonLT()) {
    m_elevator.setHeight(45.0);
  }
  else if(m_driver2.ButtonA() && m_driver2.ButtonLT()) {
    m_elevator.setHeight(25.0);
  }
  else if(m_driver2.ButtonY()) {//hatches
    m_elevator.setHeight(60.0);
  }
  else if(m_driver2.ButtonX()) {
    m_elevator.setHeight(40.0);
  }
  else if(m_driver2.ButtonA()) {
    m_elevator.setHeight(20.0);
  }
  else if(m_driver.ButtonLB()) {//raw control driver 1
     m_elevator.translateElevator(-ELEVATOR_SPEED);
  }
  else if(m_driver.ButtonRB()){
     m_elevator.translateElevator(ELEVATOR_SPEED);
  }
  else if(fabs (m_driver2.AxisLY()) > 0.1) {//raw control driver 2
     m_elevator.translateElevator(m_driver2.AxisLY()*0.7);
  }
  else if(fabs (m_driver2.AxisLY()) > 0.1){
     m_elevator.translateElevator(m_driver2.AxisLY()*0.7);
  }
  else {//maintain height
     m_elevator.translateElevator(0.07);
  }
  //   INTAKE   ///////////////////////////////////////
  if(m_driver.ButtonRT()) {
    m_intake.inOutBall(0.5);
  }
  else if(m_driver.ButtonLT()){
     m_intake.inOutBall(-1.0);
  }
  else {
     m_intake.inOutBall(0.0);
  }
  //   TILT   ///////////////////////////////////////
  if(fabs (m_driver2.AxisLY()) > 0.1) {//raw control driver 2
    m_intake.inOutAngle(m_driver2.AxisRY()*0.6);
  }
  else if(fabs (m_driver2.AxisLY()) > 0.1){
    m_intake.inOutAngle(m_driver2.AxisRY()*0.6);
  }
  else if (m_driver2.ButtonRB()){
    m_intake.encoderWrite(27);
  }
  else if (m_driver2.ButtonRT()){
    m_intake.encoderWrite(0);
  }
  else{
    m_intake.inOutAngle(0.0);
  }

  //Add driver2.ButtonB or LB push forward hatch down and out. 

  /////////////////////////////////////////
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TEST
int main() { return frc::StartRobot<Robot>(); }
#endif
