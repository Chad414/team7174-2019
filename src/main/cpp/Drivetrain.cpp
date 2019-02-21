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

void Drivetrain::resetEncoders() {
	m_lDriveF.ConfigFactoryDefault();
	m_rDriveR.ConfigFactoryDefault();
}
