// (c) 2021 MVFT. All Rights Reserved.


#include "Wing.h"

FVector AWing::CalcForces() {
	// lift
	FVector totalForce(0, 0, 0);
	auto upVec = WorldUpVector();
	upVec.Normalize();
	auto cosTheta = FVector::DotProduct(upVec, FVector(0, 0, 1));
	auto localVelVec = LocalSpaceVelocityVector();
	auto forwardVel = UKismetMathLibrary::Abs(localVelVec.X);
	totalForce += (cosTheta * forwardVel) * upVec * LiftScaleFactor;

	// Drag - perpendicular
	auto drag = FVector::DotProduct(localVelVec, FVector(0.0f, 0.0f, 1.0f)) * WingResistance;
	auto dragVec = drag * (-WorldUpVector());
	totalForce += dragVec;

	// drag - parallel
	drag = FVector::DotProduct(localVelVec, FVector(1.0f, 0.0f, 0.0f)) * ForwardResistance;
	dragVec = drag * (-WorldForwardVector());

	return totalForce;
}

FVector AWing::CalcTorques(const FVector&) {
	// angular drag - yaw

	return FVector(0, 0, 0);
}