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

	float angleOfAttack = 0;	// TODO: calculate angle of attack (normalize(drone velocity part space) dot PartForward)

	FVector2D dv_xz{ droneVelocityInPartSpace.X, droneVelocityInPartSpace.Z };
	return liftEq(Falpha(angleOfAttack),dv_xz, ro, wingArea);
}

// apply this as a negative multiplicand of (drone velocity part space)
float AWing::CalcDragInline()
{
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

	//TODO: call above functions

	return FVector{ 0,0,0 };
}

FVector AWing::CalcTorques() {

	return FVector(0, 0, 0);
}