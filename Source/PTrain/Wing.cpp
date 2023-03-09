// (c) 2021 MVFT. All Rights Reserved.


#include "Wing.h"

constexpr static float constantOfDrag = 0.0f;	// TODO: a constant based on a flat plate

template<typename T>
float liftEq(float C_L, T droneVelocityInPartSpace, float ro, float wingArea) {
	// the lift equation
	// "Size" is vector Magnitude, because Unreal could not name it something normal
	return (powf((C_L * ro * droneVelocityInPartSpace).Size(), 2) / 2) * wingArea;
}

float AWing::Falpha(float alpha) {
	//TODO: lookup in data table
	return 0;
}

// the result should be applied as a vector perpendicular to the drone's velocity vector
// only use this function if the drone is flying forward
float AWing::CalcLiftForward() {
	FVector droneVelocityInPartSpace = LocalSpaceVelocityVector();
	// if the local forward vector has negative magnitude, then the wing is not moving forward
	// so we do not want to calculate further
	if (FVector::DotProduct(droneVelocityInPartSpace, PartForwardVector()) < 0) {
		return 0;
	}

	// calculate angle of attack
	// normalize(drone velocity part space) dot PartForward
	droneVelocityInPartSpace.Normalize();
	float angleOfAttack = FVector::DotProduct(droneVelocityInPartSpace, PartForwardVector());

	FVector2D dv_xz{ droneVelocityInPartSpace.X, droneVelocityInPartSpace.Z };
	return liftEq(Falpha(angleOfAttack),dv_xz, ro, wingArea);
}

// apply this as a negative multiplicand of (drone velocity part space)
float AWing::CalcDragInline()
{
	// if the local forward vector has negative magnitude, then the wing is not moving forward
	// so we do not want to calculate further
	if (FVector::DotProduct(LocalSpaceVelocityVector() * PartForwardVector()) < 0) {
		return 0;
	}

	FVector droneVelocityInPartSpace = LocalSpaceVelocityVector();
	FVector2D dv_xz{ droneVelocityInPartSpace.X, droneVelocityInPartSpace.Z };

	return liftEq(constantOfDrag,dv_xz, ro, wingArea);
}

FVector AWing::CalcDrag()
{
	auto droneVelociytPartSpace = LocalSpaceVelocityVector();
	droneVelociytPartSpace.Normalize();

	return liftEq(constantOfDrag, FVector2D{ droneVelociytPartSpace.Z,0 }, ro, wingArea) * -droneVelociytPartSpace;
}


FVector AWing::CalcForces() {

	//these are in world space, we need them in part space
	auto liftForward = CalcLiftForward();
	auto inlinedrag = CalcDragInline();
	auto otherDrag = CalcDrag();
	auto worldSpaceForces = otherDrag + (-1 * PartForwardVector() * inlinedrag) + (PartUpVector() * liftForward);

	auto localSpace = GetActorTransform().TransformVector(worldSpaceForces);

	return localSpace;
}

FVector AWing::CalcTorques() {
	// only apply this if the wing is actively rotating
	auto localAngularVelocity = LocalSpaceAngularVelocityVector();
	if (localAngularVelocity.Size() < 0.1f) {
		FVector(0, 0, 0);
	}

	const auto inputForceLocation = (3.f / 4) * wingLength;

	// TODO: implement...

	return FVector(0, 0, 0);
}