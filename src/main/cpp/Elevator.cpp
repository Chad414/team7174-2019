#include "Elevator.h"


Elevator::Elevator()
:Lift(ELEVATOR_TALON),
lazer(frc::I2C::Port::kOnboard, 0x03)
 {
     
 }

bool Elevator::autonElevator(double height){
    currentHeight = getLazerInches();
    if ( (height - currentHeight) >= 0) {
        upDown = 1;
    }
    else {
        upDown = -1;
    }

    if (abs(height-currentHeight)>TOLERANCE_INCHES && abs(height-currentHeight)>8){
        Lift.Set(1.0 * upDown);
        return false;
    }
    else if (abs(height-currentHeight)>TOLERANCE_INCHES && abs(height-currentHeight)>6){
        Lift.Set(0.55 * upDown);
        return false;
    }
    else if (abs(height-currentHeight)>TOLERANCE_INCHES && abs(height-currentHeight)>3){
        Lift.Set(0.4 * upDown);
        return false;
    }
    else{
        Lift.Set(0.06);
        return true;
    }
}

void Elevator::translateElevator(double speed) {
    Lift.Set(speed);
 }

double Elevator::getLazerInches(){
    lazer.Read(0x03,1,&buffer);
    return buffer / 2.54;;
}

void Elevator::setHeight(double height) {
    currentHeight = getLazerInches();
    if ( (height - currentHeight) >= 0) {
        upDown = 1;
    }
    else {
        upDown = -1;
    }

    if (abs(height-currentHeight)>TOLERANCE_INCHES && abs(height-currentHeight)>8){
        Lift.Set(1.0 * upDown);
    }
    else if (abs(height-currentHeight)>TOLERANCE_INCHES && abs(height-currentHeight)>6){
        Lift.Set(0.55 * upDown);
    }
    else if (abs(height-currentHeight)>TOLERANCE_INCHES && abs(height-currentHeight)>3){
        Lift.Set(0.2 * upDown);
    }
    else if (abs(height-currentHeight)>TOLERANCE_INCHES){
        Lift.Set(0.2 * upDown);
    }
    else{
        Lift.Set(0.06);
    }
}