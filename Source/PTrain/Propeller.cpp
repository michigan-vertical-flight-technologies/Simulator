// (c) 2021 MVFT. All Rights Reserved.


#include "Propeller.h"

// read from RotationSpeed...

FVector APropeller::CalcForces() {
	auto upVec = WorldUpVector();
	return ForceScaleFactor * PowerFactor * (FVector(0, 0, currentRotationSpeed) * upVec);
}

FVector APropeller::CalcTorques(const FVector& droneRootPos) {
	auto worldPos = WorldLocation();
	auto localSpace = droneRootPos - worldPos;
	auto upVec = WorldUpVector();
	return FVector::CrossProduct(localSpace, FVector(0, 0, currentRotationSpeed) * upVec) * ForceScaleFactor;
}