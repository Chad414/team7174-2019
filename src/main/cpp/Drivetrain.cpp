#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_lSpeedGroup( m_lDriveF, m_lDriveR),
	m_rSpeedGroup(m_rDriveF, m_rDriveR),
	m_drive(m_lSpeedGroup, m_rSpeedGroup),
	m_drivePID(1/5.0, 0.0, 0.0, 0.0, 0.02),
	pidgey(&m_lDriveR)
{
		m_drive.SetSafetyEnabled(false);		
}

void Drivetrain::ArcadeDrive(double speed, double angle) {
	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(speed, angle);
}

double Drivetrain::getYaw(){
	return m_lDriveR.GetSelectedSensorPosition(0);
	pidgey.GetYawPitchRoll(xyz);
	 xyz[1];
}

//All functions for encoders
void Drivetrain::resetEncoders() {
	m_lDriveF.SetSelectedSensorPosition(0.0);
	m_rDriveR.SetSelectedSensorPosition(0.0);
}
double Drivetrain::getDistance() {
	return ((-m_lDriveF.GetSelectedSensorPosition(0) + m_rDriveR.GetSelectedSensorPosition(0)) / 2 / DRIVE_ENCODER_COUNTS_PER_FOOT);
}
double Drivetrain::getTurningDistance(){
	return ((abs(-m_lDriveF.GetSelectedSensorPosition(0)) + abs(m_rDriveR.GetSelectedSensorPosition(0))) / 2 / DRIVE_ENCODER_COUNTS_PER_FOOT);
}
double Drivetrain::getRDistance() {
	return (m_rDriveR.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT);
}
double Drivetrain::getLDistance() {
	return (-m_lDriveF.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT);
}
double Drivetrain::getRVelocity() {
	return m_rDriveR.GetSelectedSensorVelocity(0);
}
double Drivetrain::getLVelocity() {
	return -m_lDriveF.GetSelectedSensorVelocity(0);
}

//Teleop PID drive for testing.
double Drivetrain::pidDrive(double angle, double distance){
	double command = m_drivePID.compute(getDistance(), distance);
	double bias;
		if (distance >0){
			bias = 0.22;
		}
		else {
			bias = -0.22;
		}
	m_drive.ArcadeDrive(command + bias, angle);
}

//Auton control functions
bool Drivetrain::autonPID(double distance){//Straight line.
	if (abs(getDistance()) < abs(distance)){
		double command = m_drivePID.compute(getDistance(), distance);
		double bias;
		if (distance >0){
			bias = 0.22;
		}
		else {
			bias = -0.22;
		}
		m_drive.ArcadeDrive(command + bias, 0.0);
	}
	else {
		m_drive.ArcadeDrive(0.0, 0.0);
		return true;
	}
}
bool Drivetrain::autonTurning(double distance){//Only point turns. If positive then right turn, else left turn
	double leftRight;
	if (distance>0){
		leftRight = 0.5;
	}
	else {
		leftRight = -0.5;
	}
	
	if (getTurningDistance()<distance){
			m_drive.ArcadeDrive(0.0, leftRight);
	}
	else {
		m_drive.ArcadeDrive(0.0, 0.0);
		return true;
	}
}
bool Drivetrain::autonStraight(double distance){
	double forBack;
	if (distance>0){
		forBack = 0.6;
	}
	else {
		forBack = -0.6;
	}
	
	if (getDistance()<distance){
			m_drive.ArcadeDrive(forBack, 0.0);
	}
	else {
		m_drive.ArcadeDrive(0.0, 0.0);
		return true;
	}
}
bool Drivetrain::autonLimeDrive(double speed, double angle, double area){
	m_drive.ArcadeDrive(speed, angle);
	if (area > 8){
		return true;
	}
	else {
        return false;
    }
}
bool Drivetrain::autonDrivetrain(double rVelocity, double lVelocity, double rDistance, double lDistance){
	m_drive.SetSafetyEnabled(false);
	if(abs(getRDistance()) < (rDistance - 0.2)){
		//m_rSpeedGroup.Set(-velocityMultiplier(rVelocity, lVelocity, getRVelocity(), getLVelocity()));
		//m_rDriveF.Set(-velocityMultiplier(rVelocity, lVelocity, getRVelocity(), getLVelocity()));
		//m_rDriveR.Set(-velocityMultiplier(rVelocity, lVelocity, getRVelocity(), getLVelocity()));

		m_rDriveF.Set(-rVelocity);
		m_rDriveR.Set(-rVelocity);
    }
	else if(abs(getRDistance()) < rDistance){
		//m_rSpeedGroup.Set(-rVelocity);
		m_rDriveF.Set(-0.1);
		m_rDriveR.Set(-0.1);
	}
	else{
		//m_rSpeedGroup.Set(0.0);
		m_rDriveF.Set(0.0);
		m_rDriveR.Set(0.0);
	}

	if(abs(getLDistance()) < (lDistance - 0.2)){
		//m_lSpeedGroup.Set(velocityMultiplier(lVelocity, rVelocity, getLVelocity(), getRVelocity()));
		//m_lDriveF.Set(velocityMultiplier(lVelocity, rVelocity, getLVelocity(), getRVelocity()));
		//m_lDriveR.Set(velocityMultiplier(lVelocity, rVelocity, getLVelocity(), getRVelocity()));
		m_lDriveF.Set(lVelocity);
		m_lDriveR.Set(lVelocity);
	}
	else if(abs(getLDistance()) < lDistance){
		//m_lSpeedGroup.Set(lVelocity);
		m_lDriveF.Set(0.1);
		m_lDriveR.Set(0.1);
	}
	else{
		//m_lSpeedGroup.Set(0.0);
		m_lDriveF.Set(0.0);
		m_lDriveR.Set(0.0);
	}
	
	if ((abs(getRDistance()) >= rDistance) && abs(getLDistance()) >= lDistance){
		
		return true;
		//resetEncoders();

	}
	else {
		return false;
	}
}

double Drivetrain::velocityMultiplier(double firstV, double secondV, double firstEncoderSpeed, double secondEncoderSpeed){
	double ratio = (firstV/secondV);
	double vRatio = (firstEncoderSpeed/secondEncoderSpeed);
	if((vRatio/ratio) < 1.0){
		return ((ratio/vRatio) * firstV);
	}
	else{
		return 1.0 * firstV;
	}
}

/*
void Drivetrain::encoderWrite(double rightDistance, double leftDistance){
	if( (m_rDriveR.GetSelectedSensorPosition(0)) < rightDistance ){
		m_rSpeedGroup.Set(-0.2);
    }
	else{
		m_rSpeedGroup.Set(0.0);
	}

	if( (-m_lDriveF.GetSelectedSensorPosition(0)) < leftDistance ){
		m_lSpeedGroup.Set(0.2);
    }
	else{
		m_lSpeedGroup.Set(0.0);
	}
	/*
	if ( ((-m_lDriveF.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT) >= leftDistance) && (m_rDriveR.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT) >= rightDistance) {
		//m_robot.autonCase++;
	}
	
}
*/