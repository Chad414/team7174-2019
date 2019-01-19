#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_left( m_lDriveF, m_lDriveR),
	m_right(m_rDriveF, m_rDriveR),
	m_drive(m_left, m_right)


{
 
}

