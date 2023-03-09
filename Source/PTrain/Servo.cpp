// (c) 2021 MVFT. All Rights Reserved.


#include "Servo.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AServo::AServo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AServo::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AServo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto rotation = GetParentComponent()->GetRelativeRotation();
	auto currentZ = rotation.Yaw;
	auto newZ = FMath::Lerp(currentZ, targetPos, rotationRate);
	rotation.Yaw = newZ;
	GetParentComponent()->SetRelativeRotation(rotation);
}

void AServo::SetTargetPoseInDegrees(float pos) {
	targetPos = FMath::Clamp(pos, AngleBounds.X, AngleBounds.Y);
}