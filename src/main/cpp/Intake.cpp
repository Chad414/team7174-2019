#include "Intake.h"


Intake::Intake()
:LBallObtainer(LBALL_OBTAINER_VICTOR),
RBallObtainer(RBALL_OBTAINER_VICTOR),
BallAngle(BALL_ANGLE_TALON)
//angleEncoder(ANGLE_ENCODER, true)

 {
     
 }

void Intake::inOutBall(double speed) {

    LBallObtainer.Set(speed);
    RBallObtainer.Set(speed);
 }

void Intake::inOutAngle(double speed) {
    BallAngle.Set(speed);
}

double Intake::getDistance() {
    return BallAngle.GetSelectedSensorPosition(0);
}
