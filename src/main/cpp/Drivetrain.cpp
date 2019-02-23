#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_lSpeedGroup( m_lDriveF, m_lDriveR),
	m_rSpeedGroup(m_rDriveF, m_rDriveR),
	m_drive(m_lSpeedGroup, m_rSpeedGroup)
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
}
	*/



 
void Drivetrain::encoderWrite(double rightDistance, double leftDistance){

	

	if( (m_rDriveR.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_METER) < rightDistance ){
		
		m_rSpeedGroup.Set(.5);
    }
	else{
		m_rDriveR.ConfigFactoryDefault();
		m_rSpeedGroup.Set(0.0);
	}


	if( (m_lDriveR.GetSelectedSensorPosition(0) / DRIVE_ENCODER_COUNTS_PER_METER) < leftDistance ){
	
		m_lSpeedGroup.Set(.5);
    }
	else{
		m_lSpeedGroup.Set(0.0);
		m_lDriveF.ConfigFactoryDefault();
	}
   
}

void Drivetrain::resetEncoders() {
	m_lDriveF.ConfigFactoryDefault();
	m_rDriveR.ConfigFactoryDefault();
}
