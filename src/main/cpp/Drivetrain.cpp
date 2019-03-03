#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_lSpeedGroup( m_lDriveF, m_lDriveR),
	m_rSpeedGroup(m_rDriveF, m_rDriveR),
	m_drive(m_lSpeedGroup, m_rSpeedGroup)

	//m_robot()
{
		m_drive.SetSafetyEnabled(false);
}

void Drivetrain::ArcadeDrive(double speed, double angle) {
	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(speed, angle);
}

double Drivetrain::getDistance() {
	return ((-m_lDriveF.GetSelectedSensorPosition(0) + m_rDriveR.GetSelectedSensorPosition(0)) / 2);
}

double Drivetrain::getRDistance() {
	return m_rDriveR.GetSelectedSensorPosition(0);
}

double Drivetrain::getLDistance() {
	return -m_lDriveF.GetSelectedSensorPosition(0);
}

/*double Drivetrain::velocityMultiplier(){

	if(m_rDriveR.GetSelectedSensorVelocity(0) > -m_lDriveF.GetSelectedSensorVelocity(0) ){

		return (m_rDriveR.GetSelectedSensorVelocity(0)) / (-m_lDriveF.GetSelectedSensorVelocity(0));
	}
	else if (m_rDriveR.GetSelectedSensorVelocity(0) < -m_lDriveF.GetSelectedSensorVelocity(0) ){

		return (m_lDriveR.GetSelectedSensorVelocity(0)) / (m_rDriveF.GetSelectedSensorVelocity(0));
	}

	else {
		return 1.0;
	}

	//if left is faster= negative, if right faster = positive
}*/
 
void Drivetrain::encoderWrite(double rightDistance, double leftDistance){
	if( (m_rDriveR.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT) < rightDistance ){
		m_rSpeedGroup.Set(-0.2);
    }
	else{
		m_rSpeedGroup.Set(0.0);
	}

	if( (-m_lDriveF.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT) < leftDistance ){
		m_lSpeedGroup.Set(0.2);
    }
	else{
		m_lSpeedGroup.Set(0.0);
	}
/*
	if ( ((-m_lDriveF.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT) >= leftDistance) && (m_rDriveR.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_FOOT) >= rightDistance) {
		//m_robot.autonCase++;
	}
*/
}

void Drivetrain::resetEncoders() {
	m_lDriveF.SetSelectedSensorPosition(0.0);
	m_rDriveR.SetSelectedSensorPosition(0.0);
}
