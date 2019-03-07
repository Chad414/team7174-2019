#include "Intake.h"


Intake::Intake()
:LBallObtainer(LBALL_OBTAINER_VICTOR),
RBallObtainer(RBALL_OBTAINER_VICTOR),
BallAngle(BALL_ANGLE_TALON)
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
    return (BallAngle.GetSelectedSensorPosition(0)/10000);
}

double Intake::getAngleVelocity(){
    return BallAngle.GetSelectedSensorVelocity();
}

void Intake::resetEncoders() {
    BallAngle.SetSelectedSensorPosition(0.0);
    //angleEncoder->Reset();
}

void Intake::encoderWrite(double angleDistance){
	if(abs(angleDistance-getDistance())>2 && getDistance() < angleDistance ){
        BallAngle.Set(-0.5);
    }
	else if (abs(angleDistance-getDistance())>2 &&getDistance() > angleDistance){
        BallAngle.Set(0.5);
	}
    else {
        BallAngle.Set(0.0);
    }
}

bool Intake::autonAngle(double angleDistance){
	if(abs(angleDistance-getDistance())>2 && getDistance() < angleDistance ){
        BallAngle.Set(-0.5);
        return false;
    }
	else if (abs(angleDistance-getDistance())>2 &&getDistance() > angleDistance){
        BallAngle.Set(0.5);
        return false;
	}
    else {
        BallAngle.Set(0.0);
        return true;
    }
}
bool Intake::autonInOut(double speed, double seconds){
    if (timerStart = false){
        autonTimer.Start();
        timerStart = true;
    }
    LBallObtainer.Set(speed);
    RBallObtainer.Set(speed);
    
    if (autonTimer.Get()>seconds){
        autonTimer.Reset();
        timerStart = false;
        return true;
    }
    else {
        return false;
    }
}

void Intake::autonTimerPrep(){
    timerStart = false;
}