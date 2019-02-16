/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CitrusLumen.h"

CitrusLumen::CitrusLumen(){
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

bool CitrusLumen::targetLocated(){
     return table->GetNumber("tv",0.0);
}

double CitrusLumen::targetOffset_Vertical(){
     return table->GetNumber("ty",0.0);
}

double CitrusLumen::targetOffset_Horizontal(){
     return table->GetNumber("tx",0.0);
     //left offset is positive, right offset is negative
}

double CitrusLumen::targetSkew(){
     return table->GetNumber("ts",0.0);
}
double CitrusLumen::targetArea(){
     return table->GetNumber("ta",0.0);
}

double CitrusLumen::targetDistance() {
    return targetArea() * AREA_TO_DISTANCE_MULTIPLIER;
}

double CitrusLumen::limelightSpeed() {
if (targetDistance()<LIMELIGHT_MIN_DISTANCE){
    return 0;
}
else {
    return LIMELIGHT_SPEED;
}

}
