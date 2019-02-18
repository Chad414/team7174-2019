#include "Intake.h"


Intake::Intake()
:LBallObtainer(LBALL_OBTAINER_VICTOR),
RBallObtainer(RBALL_OBTAINER_VICTOR),
BallAngle(BALL_ANGLE_TALON)

 {}

void Intake::inOutBall(double speed) {

    LBallObtainer.Set(speed);
    RBallObtainer.Set(speed);
 }

void Intake::inOutAngle(double speed) {
    BallAngle.Set(speed);
}