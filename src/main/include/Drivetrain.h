#include <cmath>
#include "ctre/Phoenix.h"
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedController.h>
#include <frc/Talon.h>
//#include <frc/Encoder.h>

#define TALON_DRIVE_LF 2
#define TALON_DRIVE_LR 1
#define TALON_DRIVE_RF 4
#define TALON_DRIVE_RR 3

#define DRIVE_ENCODER_L 0
#define DRIVE_ENCODER_R 0

#define DRIVE_ENCODER_COUNTS_PER_METER 1


class Drivetrain {
public:


Drivetrain();

void ArcadeDrive(double speed, double angle);


//double getDistance();

private:


WPI_TalonSRX  m_lDriveF;
WPI_TalonSRX  m_lDriveR;
WPI_TalonSRX  m_rDriveF;
WPI_TalonSRX  m_rDriveR;

frc::SpeedControllerGroup m_lSpeedGroup;
frc::SpeedControllerGroup m_rSpeedGroup;

frc::DifferentialDrive m_drive;
/*
frc::Encoder m_lEncoder;
frc::Encoder m_rEncoder;

*/

};

