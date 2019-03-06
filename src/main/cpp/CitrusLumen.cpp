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
    return (table->GetNumber("tx",0.0));
    //left offset is positive, right offset is negative
}
double CitrusLumen::targetSkew(){
    return table->GetNumber("ts",0.0);
}
double CitrusLumen::targetArea(){
    return table->GetNumber("ta",0.0);
}

double CitrusLumen::forwardSpeed() {
    if (targetArea()>LIMELIGHT_MAX_AREA){
        return 0.0;
    }
    else if (targetArea()>10){//when area >10 slow to 0.25 power. 
        return 0.25;
    }
    else if (targetArea()>7){
        return 0.4;
    }
    else {
        return LIMELIGHT_SPEED;
    }
}

double CitrusLumen::horizontalBallSpeed(){
    currentOffset=targetOffset_Horizontal();
    if ((targetOffset_Horizontal() - getBallCorrection()) > 0 && abs( currentOffset ) > LIMELIGHT_TOLERANCE){
        return std::min(LIMELIGHT_TURNSPEED, targetOffset_Horizontal() * 0.12) ;
    }
    else if ((targetOffset_Horizontal() - getBallCorrection()) < 0 && abs( currentOffset ) > LIMELIGHT_TOLERANCE){
        return std::max(-LIMELIGHT_TURNSPEED, targetOffset_Horizontal() * 0.12);
    }
    else{
        return 0;
    }
}

double CitrusLumen::horizontalHatchSpeed(){
    currentOffset=targetOffset_Horizontal();
    if ((targetOffset_Horizontal() - getHatchCorrection()) > 0 && abs( currentOffset ) > LIMELIGHT_TOLERANCE){
        return std::min(LIMELIGHT_TURNSPEED, targetOffset_Horizontal() * 0.12) ;
    }
    else if ((targetOffset_Horizontal() - getHatchCorrection()) < 0 && abs( currentOffset ) > LIMELIGHT_TOLERANCE){
        return std::max(-LIMELIGHT_TURNSPEED, targetOffset_Horizontal() * 0.12);
    }
    else{
        return 0;
    }
}

double CitrusLumen::getBallCorrection(){
    return ballCorrectionMultiplier * targetArea();
}

double CitrusLumen::getHatchCorrection(){
    return hatchCorrectionMultiplier * targetArea();
}
