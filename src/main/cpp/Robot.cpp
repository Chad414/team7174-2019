#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot()
  : m_drivetrain(),
   m_driver(JOYSTICK_PORT),
   m_driver2(JOYSTICK2_PORT),
   m_lime(),
   m_intake(),
   m_elevator(),
   m_autonTimer()
   {
   }

void Robot::consoleOut(std::string desc, double output){
  if (consoleOutputCounter==25){
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
  m_lime.toggleLimelight(false);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_drivetrain.resetEncoders();
  m_intake.resetEncoders();
  autonCase = 0;
  m_intake.autonTimerPrep();
  autonAbort = false;
  speedMultiplier = 1.0;
  m_autonTimer.Reset();
}

void Robot::AutonomousPeriodic(){
  Robot::consoleOut("Drive encoders distance: ", m_drivetrain.getDistance());
  if (m_driver2.ButtonLB()){
    autonAbort=true;
  }
  else{}

  if (autonAbort == true){//All controller functions.
//   DRIVETRAIN   /////////////////////////////////
  if (m_driver.ButtonB() || m_driver.ButtonA()){
    m_lime.toggleLimelight(true);
  }
  else {
    m_lime.toggleLimelight(false);  
  }

  if((m_lime.targetLocated()) && (m_driver.ButtonB())) {
   	m_drivetrain.ArcadeDrive(m_lime.forwardSpeed(), m_lime.horizontalBallSpeed() );
  }
  else if((m_lime.targetLocated()) && (m_driver.ButtonA())) {
   	m_drivetrain.ArcadeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed() );
  }
  else if((fabs (m_driver.AxisLY()) > 0.1 || fabs(m_driver.AxisRX())) > 0.1 ) {
		m_drivetrain.ArcadeDrive(-(speedMultiplier * (m_driver.AxisLY())), (speedMultiplier * (m_driver.AxisRX())));
  }
  
  else if (m_driver2.ButtonY()){
    //just for preventing encoder reset.
  }
  
  else{
    m_drivetrain.ArcadeDrive(0.0, 0.0);
    m_drivetrain.resetEncoders();
  }

  if (m_driver.ButtonX()) {
    speedMultiplier = 0.7;
  }
  else if (m_driver.ButtonY()) {
    speedMultiplier = 1.0;
  }

  else{}
//   ELEVATOR   ///////////////////////////////////
  if(m_driver2.ButtonX()) {
    m_elevator.setHeightPID(BALL_MIDDLE);
  }
  else if(m_driver2.ButtonA()) {
    m_elevator.setHeightPID(BALL_BOTTOM);
  }
  else if(m_driver2.ButtonX() && m_driver2.ButtonLT()) {
    m_elevator.setHeightPID(HATCH_MIDDLE);
  }
  else if(m_driver2.ButtonA() && m_driver2.ButtonLT()) {
    m_elevator.setHeightPID(HATCH_BOTTOM);
  }
  /*
  else if(m_driver.ButtonLB() && m_elevator.getLazerInches() > 14) {//raw control driver 1
    m_elevator.translateElevator(-ELEVATOR_SPEED);
  }*/
  else if(m_driver.ButtonLB()){
    m_elevator.setHeightPID(12.0);
  }

  else if(m_driver.ButtonRB()||m_driver2.ButtonB()){
    m_elevator.setHeightPID(CARGO_SHIP);
  }

  else if(fabs (m_driver2.AxisLY()) > 0.1) {//raw control driver 2
    if (m_driver2.AxisLY() >= 0) {
    m_elevator.translateElevator(-m_driver2.AxisLY() * 1.0);
    }
    else if (m_driver2.AxisLY() < 0){
    m_elevator.translateElevator(-m_driver2.AxisLY() * 0.7);
    }
    else {}
  }

  else {//maintain height
     m_elevator.translateElevator(0.07);
     m_elevator.m_elevatorPID.reset();
  }
//   INTAKE   /////////////////////////////////////
  if(m_driver.ButtonRT()) {
    m_intake.inOutBall(-0.5);
  }
  else if(m_driver.ButtonLT()){
     m_intake.inOutBall(0.8);
  }
  else {
     m_intake.inOutBall(0.0);
  }
//   TILT   ///////////////////////////////////////
  if(fabs (m_driver2.AxisRY()) > 0.1) {//raw control driver 2
    m_intake.inOutAngle(m_driver2.AxisRY() * -1.0);
  }
  else if (m_driver2.ButtonRB()){
    m_intake.encoderWrite(0);
  }
  else if (m_driver2.ButtonRT()){
    m_intake.encoderWrite(160);
  }
  else{
    m_intake.inOutAngle(0.0);
  }
//   HATCH DISENGAGE   ////////////////////////////
  if (m_driver2.ButtonY()){
    switch (hatchDisengageCase){
      case 0:
      if (m_drivetrain.autonTurning(0.04)){
        std::cout<<"case 0"<<std::endl;
        m_drivetrain.resetEncoders();hatchDisengageCase++;}break;

      case 1:
      m_autonTimer.Start();
      if (m_autonTimer.Get() > 1.0) {
        m_elevator.setHeightPID(14);
        hatchDisengageCase++;
        m_autonTimer.Stop();
        m_autonTimer.Reset();
      }
      break;

      case 2:
      if (m_drivetrain.autonPID(-1.0)){
        std::cout<<"case 2"<<std::endl;
        m_drivetrain.resetEncoders();hatchDisengageCase++;}break;
    }
  }
  else{
    hatchDisengageCase = 0;
    m_autonTimer.Stop();
    m_autonTimer.Reset();
  }
}
  
  
  else {
  if (START_POSITION == 1) /*RIGHT START (Timer testing) */ {
    switch (autonCase){
      case 0://Drive off platform.
      if (m_drivetrain.autonStraight(3.0)){
        m_drivetrain.resetEncoders();autonCase++;}break;

      case 1:
       m_autonTimer.Start();
        if (m_autonTimer.Get() > 5.0) {
          if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
            m_drivetrain.resetEncoders();
            autonCase++;
            m_autonTimer.Stop();
            m_autonTimer.Reset();
          }
        }
      break;

      case 2:
      if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
        m_drivetrain.resetEncoders();autonCase++;}break;
      
      case 3:
      if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
        m_autonTimer.Start();
        if (m_autonTimer.Get() > 5.0) {
          m_drivetrain.resetEncoders();
          autonCase++;
          m_autonTimer.Stop();
          m_autonTimer.Reset();
        }
      }
      break;
    }
  }

  else if (START_POSITION == -1) /*LEFT START (PID testing) */ {
    switch (autonCase){
    case 0:
      if (m_drivetrain.autonPID(2.0)){
        std::cout<<"case 0"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    case 1:
      if (m_drivetrain.autonTurning(1.5)){
        std::cout<<"case 1"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    case 2:
      if (m_drivetrain.autonPID(2.0)){
        std::cout<<"case 2"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    case 3:
      if (m_drivetrain.autonTurning(1.5)){
        std::cout<<"case 3"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    case 4:
      if (m_drivetrain.autonPID(2.0)){
        std::cout<<"case 4"<<std::endl;
        autonCase++;}break;
    case 5:
      if (m_drivetrain.autonTurning(1.5)){
        std::cout<<"case 5"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    case 6:
      if (m_drivetrain.autonPID(2.0)){
        std::cout<<"case 6"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    case 7:
      if (m_drivetrain.autonTurning(1.5)){
        std::cout<<"case 7"<<std::endl;
        m_drivetrain.resetEncoders();
        autonCase++;}break;
    }
  }

  else if (START_POSITION == 0) /*CENTER START*/ {
    if (CENTER_TRANSPORT_RIGHTLEFT==1){//center right
      switch (autonCase){
        case 0://Drive off platform.
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 1:
        if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 2:
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 3:
        if (m_drivetrain.autonDrivetrain(0.4, -0.4, 1.0, 1.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 4:
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 5://Limelight
        if (m_drivetrain.autonLimeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed(), m_lime.targetArea())){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 6://Raise elevator
        if (m_elevator.autonElevator(HATCH_BOTTOM)){
          autonCase++;}break;
        case 7://Lower tilt to horizontal
        if (m_intake.autonAngle(160)){
          autonCase++;}break;
      }
    }

    else if (CENTER_TRANSPORT_RIGHTLEFT==-1){//center left
      switch (autonCase){
        case 0://Drive off platform.
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 1:
        if (m_drivetrain.autonDrivetrain(0.4, -0.4, 1.0, 1.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 2:
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 3:
        if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 4:
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 5://Limelight
        if (m_drivetrain.autonLimeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed(), m_lime.targetArea())){
          m_drivetrain.resetEncoders();autonCase++;}break;
        case 6://Raise elevator
        if (m_elevator.autonElevator(HATCH_BOTTOM)){
          autonCase++;}break;
        case 7://Lower tilt to horizontal
        if (m_intake.autonAngle(160)){
          autonCase++;}break;
      }
    }
  }

  else if (START_POSITION == 3) /*CENTER START TIMER TEST */{
    switch (autonCase){

        case 0://Drive off platform.
        if (m_drivetrain.autonDrivetrain(0.4, 0.4, 3.0, 3.0)){
          m_drivetrain.resetEncoders();autonCase++;}break;

        case 1:
        m_autonTimer.Start();
        if (m_autonTimer.Get() > 5.0) {
          if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
            m_drivetrain.resetEncoders();
            autonCase++;
            m_autonTimer.Stop();
            m_autonTimer.Reset();
          }
        }
        break;

        case 2:
        m_autonTimer.Start();
        if (m_autonTimer.Get() > 5.0) {
          if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
            m_drivetrain.resetEncoders();
            autonCase++;
            m_autonTimer.Stop();
            m_autonTimer.Reset();
          }
        }
        break;

        case 3:
        m_autonTimer.Start();
        if (m_autonTimer.Get() > 5.0) {
          if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
            m_drivetrain.resetEncoders();
            autonCase++;
            m_autonTimer.Stop();
            m_autonTimer.Reset();
          }
        }
        break;

        case 4:
        m_autonTimer.Start();
        if (m_autonTimer.Get() > 5.0) {
          if (m_drivetrain.autonDrivetrain(-0.4, 0.4, 1.0, 1.0)){
            m_drivetrain.resetEncoders();
            autonCase++;
            m_autonTimer.Stop();
            m_autonTimer.Reset();
          }
        }
        break;

        case 5://Limelight
        if (m_drivetrain.autonLimeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed(), m_lime.targetArea())){
          m_drivetrain.resetEncoders();autonCase++;}break;

        case 6://Raise elevator
        if (m_elevator.autonElevator(HATCH_BOTTOM)){
          autonCase++;}break;
          
        case 7://Lower tilt to horizontal
        if (m_intake.autonAngle(160)){
          autonCase++;}break;
      }
  }

  else{}
  }
}

//Robot::consoleOut("Left Encoder distance: ", m_drivetrain.getLDistance());
//Robot::consoleOut("Right Encoder distance: ", m_drivetrain.getRDistance());




void Robot::TeleopInit() {
  m_drivetrain.resetEncoders();
  //m_intake.resetEncoders();
  speedMultiplier = 1.0;
}

void Robot::TeleopPeriodic() {
//   COUT   ///////////////////////////////////////
  Robot::consoleOut("range: ", m_elevator.getLazerInches());
  //Robot::consoleOut("Angle encoder counts: ", m_intake.getDistance());
  //Robot::consoleOut("Angle Velocity: ", m_intake.getAngleVelocity());
  
  //Robot::consoleOut("filtMeas: ", m_elevator.m_elevatorPID.getFiltMeas());
  //Robot::consoleOut("error: ", m_elevator.m_elevatorPID.getError());
  //Robot::consoleOut("command: ", m_elevator.m_elevatorPID.getCommand());
  //Robot::consoleOut("command drive: ", m_drivetrain.m_drivePID.getCommand());

  //Robot::consoleOut("Drive encoders distance: ", m_drivetrain.getDistance());
  //Robot::consoleOut("Left Encoder distance: ", m_drivetrain.getLDistance());
  //Robot::consoleOut("Right Encoder distance: ", m_drivetrain.getRDistance());
  //Robot::consoleOut("tilt distance: ", m_drivetrain.getYaw());

  //Robot::consoleOut("Limelight ta: ", m_lime.targetDistance());
  //Robot::consoleOut("Limelight target detected: ", m_lime.targetLocated());
  //Robot::consoleOut("Limelight Speed: ", m_lime.limelightSpeed());
  //Robot::consoleOut("Limelight Ball distance: ", m_lime.getBallDistance());
  //Robot::consoleOut("limelightl hatch distance: ", m_lime.getHatchDistance());
  //Robot::consoleOut("Limelight target vertical angle: ", m_lime.targetOffset_Horizontal());

//   DRIVETRAIN   /////////////////////////////////
  if (m_driver.ButtonB() || m_driver.ButtonA()){
    m_lime.toggleLimelight(true);
  }
  else {
    m_lime.toggleLimelight(false);  
  }

  if((m_lime.targetLocated()) && (m_driver.ButtonB())) {
   	m_drivetrain.ArcadeDrive(m_lime.forwardSpeed(), m_lime.horizontalBallSpeed() );
  }
  else if((m_lime.targetLocated()) && (m_driver.ButtonA())) {
   	m_drivetrain.ArcadeDrive(m_lime.forwardSpeed(), m_lime.horizontalHatchSpeed() );
  }
  else if((fabs (m_driver.AxisLY()) > 0.1 || fabs(m_driver.AxisRX())) > 0.1 ) {
		m_drivetrain.ArcadeDrive(-(speedMultiplier * (m_driver.AxisLY())), (speedMultiplier * (m_driver.AxisRX())));
  }
  
  //else if (m_driver2.ButtonY()){
    //just for preventing encoder reset.
  //}
  
  else{
    m_drivetrain.ArcadeDrive(0.0, 0.0);
    m_drivetrain.resetEncoders();
  }

  if (m_driver.ButtonX()) {
    speedMultiplier = 0.7;
  }
  else if (m_driver.ButtonY()) {
    speedMultiplier = 1.0;
  }

  else{}
//   ELEVATOR   ///////////////////////////////////
  if(m_driver2.ButtonLT()) {
    m_elevator.setHeightPID(HATCH_MIDDLE);
  }
  else if(m_driver2.ButtonY()) {
    m_elevator.setHeightPID(HATCH_BOTTOM);
  }
  else if(m_driver2.ButtonA()) {
    m_elevator.setHeightPID(BALL_BOTTOM);
  }
  else if(m_driver2.ButtonX()) {
    m_elevator.setHeightPID(BALL_MIDDLE);
  }

  else if(m_driver.ButtonLB()){
    m_elevator.setHeightPID(12.0);
  }

  else if(m_driver.ButtonRB()||m_driver2.ButtonB()){
    m_elevator.setHeightPID(CARGO_SHIP);
  }

  else if(fabs (m_driver2.AxisLY()) > 0.1) {//raw control driver 2
    if (m_driver2.AxisLY() >= 0) {
    m_elevator.translateElevator(-m_driver2.AxisLY() * 1.0);
    }
    else if (m_driver2.AxisLY() < 0){
    m_elevator.translateElevator(-m_driver2.AxisLY() * 0.7);
    }
    else {}
  }

  else {//maintain height
     m_elevator.translateElevator(0.07);
     m_elevator.m_elevatorPID.reset();
  }
//   INTAKE   /////////////////////////////////////
  if(m_driver.ButtonRT()) {
    m_intake.inOutBall(-0.5);
  }
  else if(m_driver.ButtonLT()){
    m_intake.inOutBall(0.8);
  }
  else {
    m_intake.inOutBall(0.0);
  }
//   TILT   ///////////////////////////////////////
  if(fabs (m_driver2.AxisRY()) > 0.1) {//raw control driver 2
    m_intake.inOutAngle(m_driver2.AxisRY() * -1.0);
  }
  else if (m_driver2.ButtonRB()){//reset to up position
    m_intake.encoderWrite(0);
  }
  else if (m_driver2.ButtonRT()){
    m_intake.encoderWrite(160);
  }
  else{
    m_intake.inOutAngle(0.0);
  }
//   HATCH DISENGAGE   ////////////////////////////
  /*
  if (m_driver2.ButtonY()){
    switch (hatchDisengageCase){
      case 0:
      if (m_drivetrain.autonTurning(0.04)){
        std::cout<<"case 0"<<std::endl;
        m_drivetrain.resetEncoders();hatchDisengageCase++;}break;

      case 1:
      m_autonTimer.Start();
      if (m_autonTimer.Get() > 1.0) {
        m_elevator.setHeightPID(14);
        hatchDisengageCase++;
        m_autonTimer.Stop();
        m_autonTimer.Reset();
      }
      break;

      case 2:
      if (m_drivetrain.autonPID(-1.0)){
        std::cout<<"case 2"<<std::endl;
        m_drivetrain.resetEncoders();hatchDisengageCase++;}break;
    }
  }
  else{
    hatchDisengageCase = 0;
    m_autonTimer.Stop();
    m_autonTimer.Reset();
  }
  */
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TEST
int main() { return frc::StartRobot<Robot>(); }
#endif
