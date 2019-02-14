#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_lSpeedGroup( m_lDriveF, m_lDriveR),
	m_rSpeedGroup(m_rDriveF, m_rDriveR),
	m_drive(m_lSpeedGroup, m_rSpeedGroup)
	//m_lEncoder(DRIVE_ENCODER_L, true),
	//m_rEncoder(DRIVE_ENCODER_R, false)
{

		m_drive.SetSafetyEnabled(false);

}

void Drivetrain::ArcadeDrive(double speed, double angle) {
	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(speed, angle);
}
/*
double Drivetrain::getDistance() {
	return ((m_lEncoder.GetDistance() + m_rEncoder.GetDistance()) / 2) / DRIVE_ENCODER_COUNTS_PER_METER;
}

*/