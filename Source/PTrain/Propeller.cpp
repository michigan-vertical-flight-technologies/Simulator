// (c) 2021 MVFT. All Rights Reserved.


#include "Propeller.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/CurveTable.h"
#include "Constants.h"


// read from RotationSpeed...

FVector APropeller::CalcForces() {
	auto upVec = PartUpVector();
	return ForceScaleFactor * getThrustForRPM(getCurrentRPM()) * upVec;
}

FVector APropeller::CalcTorques() {
	auto currentAM = LocalSpaceAngularVelocityVector() * momentOfInertia * PartUpVector();
	auto now = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	auto torque = (currentAM - prevTickAngularMomentum) / (now - prevTickTime);	// a super basic derivative
	prevTickTime = now;
	return torque;	
}

void APropeller::Tick(float DeltaTime)
{
	if (prevTickTime == 0) {
		prevTickTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	}
	AddActorLocalRotation(FRotator(0, 20, 0) * currentRotationSpeed);
}

float APropeller::getCurrentRPM()
{
	return currentRotationSpeed * maximumRPM;
}

float APropeller::getThrustForRPM(float rpm)
{
	auto value = thrustRPMCurve->Eval(rpm);
	return value;
}

void APropeller::BeginPlay()
{
	Super::BeginPlay();
	thrustRPMCurve = thrustLookupTable->FindSimpleCurve(DATA_RPMTHRUST_NAME, "", true);
	if (!thrustRPMCurve) {
		UE_LOG(LogTemp, Error, TEXT("Propeller curve table does not have %s"), DATA_RPMTHRUST_NAME);
	}
}
