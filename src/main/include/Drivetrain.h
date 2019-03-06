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
#define DRIVE_ENCODER_COUNTS_PER_FOOT 535

class Drivetrain {

public:
Drivetrain();
void ArcadeDrive(double speed, double angle);

double getDistance();
double getRDistance();
double getLDistance();
double getRVelocity();
double getLVelocity();

void resetEncoders();
void encoderWrite(double rightDistance, double leftDistance);
bool autonDrivetrain(double rVelocity, double lVelocity, double rDistance, double lDistance);
double velocityMultiplier(double firstV, double secondV, double firstEncoderSpeed, double secondEncoderSpeed);

private:
WPI_TalonSRX  m_lDriveF;
WPI_TalonSRX  m_lDriveR;
WPI_TalonSRX  m_rDriveF;
WPI_TalonSRX  m_rDriveR;
frc::SpeedControllerGroup m_lSpeedGroup;
frc::SpeedControllerGroup m_rSpeedGroup;
frc::DifferentialDrive m_drive;

//Robot m_robot;
};