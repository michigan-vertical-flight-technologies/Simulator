// (c) 2021 MVFT. All Rights Reserved.


#include "DebugFlightController.h"

void ADebugFlightController::RegisterMotor(AMotor* motor) {
	allMotors.Add(motor);
	motor->PropagateSpeed(0.5);
}

void ADebugFlightController::RegisterServo(AServo* servo) {
	allServos.Add(servo);
}

void ADebugFlightController::Switch() {
	for (auto servo : allServos) {
		servo->SetTargetPoseInDegrees(-90);
	}
}