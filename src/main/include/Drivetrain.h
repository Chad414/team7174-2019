#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedController.h>
#include <frc/Talon.h>

#define TALON_DRIVE_LF 2
#define TALON_DRIVE_LR 1
#define TALON_DRIVE_RF 4
#define TALON_DRIVE_RR 3


class Drivetrain {
public:
	Drivetrain();
private:

frc::Talon  m_lDriveF;
frc::Talon  m_lDriveR;
frc::Talon  m_rDriveF;
frc::Talon  m_rDriveR;

frc::SpeedControllerGroup m_lSpeedGroup;
frc::SpeedControllerGroup m_rSpeedGroup;

frc::DifferentialDrive m_drive;

};

