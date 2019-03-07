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
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_drivetrain.resetEncoders();
  m_intake.resetEncoders();
  autonCase = 0;
  m_intake.autonTimerPrep();
}

void Robot::AutonomousPeriodic(){//tilt down 39 to 

  Robot::consoleOut("Left Encoder distance: ", m_drivetrain.getLDistance());
  Robot::consoleOut("Right Encoder distance: ", m_drivetrain.getRDistance());

  if (START_POSITION == 1) /*RIGHT START*/ {
    switch (autonCase){
  
      case 0://Drive off platform.
      if (m_drivetrain.autonDrivetrain(0.3, 0.3, 3.2, 3.2)){
        std::cout<<"step 1 done"<<std::endl;
        autonCase++;}break;
       
      case 1://Turn toward rocket.
      if (m_drivetrain.autonDrivetrain(0.5, -0.5, 0.75, 0.75)){
        std::cout<<"step 2 done"<<std::endl;
        autonCase++;}break;

      case 2://Drive forward toward rocket.
      if (m_drivetrain.autonDrivetrain(0.5, 0.5, 3.0, 3.0)){
        std::cout<<"step 3 done"<<std::endl;
        autonCase++;}break;

      case 3://hatch limelight
      if (m_drivetrain.autonLimeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed(), m_lime.targetArea())){
        autonCase++;}break;
      case 4://lower intake angle and raise elevator
      if (m_intake.autonAngle(-60)){
        autonCase++;}break;
      /*    
      case 4://deploy hatch
      if (m_drivetrain.autonDrivetrain(0.4, 0.4, 1.0, 1.0)){
        autonCase++;}break;
    
      case 5://lower elevator
      if (m_elevator.autonElevator(18)){
       autonCase++;}break;

      case 6://back robot
      if (m_drivetrain.autonDrivetrain(-0.4, -0.4, 1.0, 1.0)){
       autonCase++;}break;
       */
    }
  }

  else if (START_POSITION == -1) /*LEFT START*/ {
    switch (autonCase){
    case 0://Drive off platform.
      if (m_drivetrain.autonDrivetrain(0.8, 0.8, 4.0, 4.0)){
        autonCase++;}break;

      case 1://Turn toward rocket.
      if (m_drivetrain.autonDrivetrain(-0.5, 0.5, 1.0, 1.0)){
        autonCase++;}break;

      case 2://Drive forward toward rocket.
      if (m_drivetrain.autonDrivetrain(0.5, 0.5, 3.0, 3.0)){
        autonCase++;}break;

      case 3://hatch limelight and lower intake angle and raise elevator
      if (m_intake.autonAngle(-60) && m_elevator.autonElevator(15) && m_drivetrain.autonLimeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed(), m_lime.targetArea())){
        autonCase++;}break;
    
      case 4://deploy hatch
      if (m_drivetrain.autonDrivetrain(0.4, 0.4, 1.0, 1.0)){
        autonCase++;}break;
    
      case 5://lower elevator
      if (m_elevator.autonElevator(18)){
       autonCase++;}break;

      case 6://back robot
      if (m_drivetrain.autonDrivetrain(-0.4, -0.4, 1.0, 1.0)){
       autonCase++;}break;
    }
  }

  else if (START_POSITION == 0) /*CENTER START*/ {
    switch (autonCase){

      case 0://Drive off platform.
      if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
      autonCase++;}break;

      case 1://hatch limelight and lower intake angle and raise elevator
      if (m_intake.autonAngle(-60) && m_elevator.autonElevator(15) && m_drivetrain.autonLimeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed(), m_lime.targetArea())){
        autonCase++;}break;
    
      case 2://deploy hatch
      if (m_drivetrain.autonDrivetrain(0.4, 0.4, 1.0, 1.0)){
        autonCase++;}break;
    
      case 3://lower elevator
      if (m_elevator.autonElevator(18)){
       autonCase++;}break;

      case 4://back robot
      if (m_drivetrain.autonDrivetrain(-0.4, -0.4, 1.0, 1.0)){
       autonCase++;}break;
    }
  }

  else{}
}

void Robot::TeleopInit() {
  m_drivetrain.resetEncoders();
  m_intake.resetEncoders();
  speedMultiplier = 1.0;
  m_lime.toggleLimelight(false);
}

void Robot::TeleopPeriodic() {
//   COUT   ///////////////////////////////////////
  //Robot::consoleOut("range: ", m_elevator.getLazerInches());
  //Robot::consoleOut("Angle encoder counts: ", m_intake.getDistance());
  //Robot::consoleOut("Angle Velocity: ", m_intake.getAngleVelocity());

  Robot::consoleOut("Drive encoders distance: ", m_drivetrain.getDistance());
  //Robot::consoleOut("Left Encoder distance: ", m_drivetrain.getLDistance());
  //Robot::consoleOut("Right Encoder distance: ", m_drivetrain.getRDistance());

  //Robot::consoleOut("Limelight ta: ", m_lime.targetDistance());
  //Robot::consoleOut("Limelight target detected: ", m_lime.targetLocated());
  //Robot::consoleOut("Limelight Speed: ", m_lime.limelightSpeed());


//   DRIVETRAIN   /////////////////////////////////
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
    m_drivetrain.ArcadeDrive(0.0, 0.0);
    m_lime.toggleLimelight(false);
  }

  if (m_driver.ButtonX()) {
    speedMultiplier = 0.5;
  }
  else if (m_driver.ButtonY()) {
    speedMultiplier = 1.0;
  }
  else{}
//   ELEVATOR   ///////////////////////////////////
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
    m_elevator.setHeight(96.25);
  }
  else if(m_driver2.ButtonX()) {
    m_elevator.setHeight(64.0);
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
     m_elevator.translateElevator(-m_driver2.AxisLY()*0.7);
  }
  else if(fabs (m_driver2.AxisLY()) > 0.1){
     m_elevator.translateElevator(-m_driver2.AxisLY()*0.7);
  }
  else {//maintain height
     m_elevator.translateElevator(0.07);
  }
//   INTAKE   /////////////////////////////////////
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
  if(fabs (m_driver2.AxisRY()) > 0.1) {//raw control driver 2
    m_intake.inOutAngle(m_driver2.AxisRY()*0.6);
  }
  else if(fabs (m_driver2.AxisRY()) > 0.1){
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
