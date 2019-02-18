/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Elevator.h"


Elevator::Elevator()
:Lift(ELEVATOR_TALON)

 {ultra = new frc::Ultrasonic(0,1);
 ultra->SetAutomaticMode(true);
 }

void Elevator::translateElevator(double speed) {

    Lift.Set(speed);
 }

double Elevator::getUltraInches(){
    return ultra->GetRangeInches();
}

void Elevator::setHeight(double height){
    double tolerance = 1;
    double currentHeight = getUltraInches();


    if (currentHeight<height && abs(height-currentHeight)>tolerance){
        Lift.Set(0.5);
    }
    else if (getUltraInches()>height  && abs(height-currentHeight)>tolerance){
        Lift.Set(-0.5);
    }
    else{
        Lift.Set(0.06);
    }
}
