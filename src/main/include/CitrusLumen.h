/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class CitrusLumen {
 public:
  CitrusLumen();

  bool targetLocated();

  double targetOffset_Vertical();
  double targetOffset_Horizontal();
  double targetSkew();
  
 private:
  std::shared_ptr<NetworkTable> table;
};
