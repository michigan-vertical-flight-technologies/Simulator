// (c) 2021 MVFT. All Rights Reserved.


#include "Drone.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Servo.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	collision->SetSimulatePhysics(true);
	collision->SetEnableGravity(true);
	collision->SetCollisionProfileName(TEXT("PhysicsActor"));
	RootComponent = collision;
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	startPos = GetActorLocation();

	// grab the subobjects
	TArray<AActor*> allChildren;
	GetAllChildActors(allChildren, true);
	// first find the FlightController
	for (const auto actor : allChildren) {
		if (auto controller = Cast<AFlightControllerBase>(actor)) {
			activeFlightController = controller;
			break;
		}
	}
	// drone must have a flight controller!
	check(activeFlightController != nullptr);

	for (const auto actor : allChildren) {
		if (auto motor = Cast<AMotor>(actor)) {
			activeFlightController->RegisterMotor(motor);
		}
		else if (auto staticPart = Cast<AStaticPart>(actor)) {
			allParts.Add(staticPart);
		}
		else if (auto servo = Cast<AServo>(actor)) {
			activeFlightController->RegisterServo(servo);
		}
	}
}


// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float totalMassKg = 0;
	// grab all the forces and torques
	// apply it to the craft
	auto dronePos = GetActorLocation();
	for (auto part : allParts) {
		collision->AddForce(part->CalcForces());
		collision->AddTorque(part->CalcTorques(dronePos));
		totalMassKg += part->massKg;
	}
	collision->SetMassOverrideInKg(NAME_None, totalMassKg);

#if 0
	auto localVelVec = UKismetMathLibrary::InverseTransformDirection(GetTransform(), GetVelocity());
	auto forwardVel = -localVelVec.X;

	if (isHovering) {
	
	}
	else {
		// glide

		auto FRThrust = ThrustFrontRight(power);
		auto FLThrust = ThrustFrontLeft(power);

		auto FrontVec = -GetActorForwardVector();
		collision->AddForce(FrontVec * FRThrust);
		collision->AddForce(FrontVec * FLThrust);

		// Ruddervator positions
		float LRVAngle = MaxRuddervatorAngle * (currentYaw + currentPitch) / 2, 
			RRVAngle = MaxRuddervatorAngle * (currentYaw + currentPitch) / 2;

		// Ruddervators on V-tail
		//collision->AddTorque(UKismetMathLibrary::TransformDirection(GetTransform(), FVector(forwardVel * LRVAngle * RollScaleFactor, 0, 0)));
		//collision->AddTorque(-UKismetMathLibrary::TransformDirection(GetTransform(), FVector(forwardVel * RRVAngle * RollScaleFactor, 0, 0)));

		// aileron positions
		float LAileronAngle = 0, RAileronAngle = 0;
		LAileronAngle = MaxAileronAngle * -currentBank;	
		RAileronAngle = MaxAileronAngle * currentBank;

		// aileron roll torque
		collision->AddTorque(UKismetMathLibrary::TransformDirection(GetTransform(), FVector(forwardVel * LAileronAngle * RollScaleFactor,0,0)));
		collision->AddTorque(-UKismetMathLibrary::TransformDirection(GetTransform(), FVector(forwardVel * RAileronAngle * RollScaleFactor,0,0)));

		// aileron pitch torque
		//collision->AddTorque(UKismetMathLibrary::TransformDirection(GetTransform(), FVector(0, forwardVel * LAileronAngle * RollScaleFactor, 0)));
		//collision->AddTorque(UKismetMathLibrary::TransformDirection(GetTransform(), FVector(0, forwardVel * RAileronAngle * RollScaleFactor, 0)));
	}	


	// angular drag - yaw
	collision->AddTorque(-collision->GetPhysicsAngularVelocityInRadians() * AngularDrag * ForceScaleFactor);
#endif
}

void ADrone::Reset() {
	SetActorLocation(startPos);
	collision->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
	collision->SetAllPhysicsAngularVelocityInDegrees(FVector(0, 0, 0));
}