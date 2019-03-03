/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Elevator.h"


Elevator::Elevator()
:Lift(ELEVATOR_TALON)
//ultra(0,1)

 {
    ultra = new frc::Ultrasonic(0,1);
    ultra->SetAutomaticMode(true);
    //ai = new frc::AnalogInput(0);

    //ultra.SetAutomaticMode(true);
 }

void Elevator::translateElevator(double speed) {

    Lift.Set(speed);
 }

double Elevator::getUltraInches(){
    //return ultra.GetRangeInches();
    return ultra->GetRangeInches();
}

void Elevator::setHeight(double height) {
    currentHeight = getUltraInches();
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
        Lift.Set(0.4 * upDown);
    }
    else{
        Lift.Set(0.06);
    }
}


/*


    else if (getUltraInches()>height  && abs(height-currentHeight)>TOLERANCE_INCHES){
        Lift.Set(-0.5);
    }




 double Elevator::getUltra2Inches(){
    return (ai->GetVoltage() * (VOLTAGE_MULTIPLIER));
}*/