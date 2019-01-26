/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ProtoJoystick.h"

ProtoJoystick::ProtoJoystick(unsigned int port) 
: Joystick(port) {
f_A = f_B = f_X = f_Y = f_LB = f_RB = f_Back = f_Start = f_L3 = f_R3 = f_LT = f_RT = false;
}


bool ProtoJoystick::Button(int btn) {
	if ((btn & kButtonA) && !Button(kButtonA)) {
		return false;
	} else if ((btn & kButtonB) && !Button(kButtonB)) {
		return false;
	} else if ((btn & kButtonX) && !Button(kButtonX)) {
		return false;
	} else if ((btn & kButtonY) && !Button(kButtonY)) {
		return false;
	} else if ((btn & kButtonLB) && !Button(kButtonLB)) {
		return false;
	} else if ((btn & kButtonRB) && !Button(kButtonRB)) {
		return false;
	} else if ((btn & kButtonLT) && !Button(kButtonLT)) {
		return false;
	} else if ((btn & kButtonRT) && !Button(kButtonRT)) {
		return false;
	}

	return true;
}

bool ProtoJoystick::ButtonPressed(kButton btn) {
	switch (btn) {
	case kButtonA:
		if (Button(btn)) {
			return (f_A) ? false : f_A = true;
		} else {
			return f_A = false;
		}
	case kButtonB:
		if (Button(btn)) {
			return (f_B) ? false : f_B = true;
		} else {
			return f_B = false;
		}
	case kButtonX:
		if (Button(btn)) {
			return (f_X) ? false : f_X = true;
		} else {
			return f_X = false;
		}
	case kButtonY:
		if (Button(btn)) {
			return (f_Y) ? false : f_Y = true;
		} else {
			return f_Y = false;
		}
	case kButtonLB:
		if (Button(btn)) {
			return (f_LB) ? false : f_LB = true;
		} else {
			return f_LB = false;
		}
	case kButtonRB:
		if (Button(btn)) {
			return (f_RB) ? false : f_RB = true;
		} else {
			return f_RB = false;
		}
	case kButtonBack:
		if (Button(btn)) {
			return (f_Back) ? false : f_Back = true;
		} else {
			return f_Back = false;
		}
	case kButtonStart:
		if (Button(btn)) {
			return (f_Start) ? false : f_Start = true;
		} else {
			return f_Start = false;
		}
	case kButtonL3:
		if (Button(btn)) {
			return (f_L3) ? false : f_L3 = true;
		} else {
			return f_L3 = false;
		}
	case kButtonR3:
		if (Button(btn)) {
			return (f_R3) ? false : f_R3 = true;
		} else {
			return f_R3 = false;
		}
	case kButtonLT:
		if (Button(btn)) {
			return (f_LT) ? false : f_LT = true;
		} else {
			return f_LT = false;
		}
	case kButtonRT:
		if (Button(btn)) {
			return (f_RT) ? false : f_RT = true;
		} else {
			return f_RT = false;
		}
	default:
		return false;
	}
}



float ProtoJoystick::Axis(kAxis axis) {
 switch(axis) {
	case kAxisLX:
		return GetRawAxis(0);
		break;
	case kAxisLY:
		return GetRawAxis(1);
		break;
	case kAxisLT:
		return GetRawAxis(2);
		break;
	case kAxisRT:
		return GetRawAxis(3);
		break;
	case kAxisRX:
		return GetRawAxis(4);
		break;
	case kAxisRY:
		return GetRawAxis(5);
		break;
	default:
		return 0.0;
}
}
