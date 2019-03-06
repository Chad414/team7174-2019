#include "Intake.h"


Intake::Intake()
:LBallObtainer(LBALL_OBTAINER_VICTOR),
RBallObtainer(RBALL_OBTAINER_VICTOR),
BallAngle(BALL_ANGLE_TALON)
 {
     
//angleEncoder = new frc::Encoder(0, 1, false, frc::Encoder::EncodingType::k4X);
 }

 double Intake::getEncoder2Distance(){

     //return angleEncoder->Get();
    
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