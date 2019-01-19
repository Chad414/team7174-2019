#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>

#define TALON_DRIVE_LF 2
#define TALON_DRIVE_LR 1
#define TALON_DRIVE_RF 4
#define TALON_DRIVE_RR 3


class Drivetrain {
public:
	Drivetrain();
private:

TalonSRX m_lDriveF;
TalonSRX m_lDriveR;
TalonSRX m_rDriveF;
TalonSRX m_rDriveR;
	
};

