#include "Intake.h"


Intake::Intake()
:BallObtainer(BALL_OBTAINER_TALON),
BallAngle(BALL_ANGLE_TALON)

 {}

void Intake::inOutBall(double speed) {

    BallObtainer.Set(speed);
 }

void Intake::inOutAngle(double speed) {
    BallAngle.Set(speed);
}