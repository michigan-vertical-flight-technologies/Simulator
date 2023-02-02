// (c) 2021 MVFT. All Rights Reserved.


#include "Propeller.h"

// read from RotationSpeed...

FVector APropeller::CalcForces() {
	auto upVec = WorldUpVector();
	return ForceScaleFactor * 1 * (currentRotationSpeed * upVec);
}

FVector APropeller::CalcTorques() {

	return FVector{ 0,0,0 };	//TODO: see math doc for propeller torque
}