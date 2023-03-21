// (c) 2021 MVFT. All Rights Reserved.


#include "Motor.h"
#include <cassert>
#include "Engine/CurveTable.h"
constexpr auto DATA_MOTORTORQUE_NAME = "Motor.TorqueByPower";

// Sets default values
AMotor::AMotor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMotor::BeginPlay()
{
	Super::BeginPlay();
	auto parent = (GetParentComponent());
	
	TArray<USceneComponent*> childComponents;
	parent->GetChildrenComponents(true, childComponents);

	for (auto comp : childComponents) {
		if (auto ptr = Cast<UChildActorComponent>(comp)) {
			childPropeller = Cast<APropeller>(ptr->GetChildActor());
		}
	}

	// get the curve data
	torqueByPowerCurve = torqueByPowerLookupTable->FindSimpleCurve(DATA_MOTORTORQUE_NAME, "", true);
	if (!torqueByPowerCurve) {
		UE_LOG(LogTemp, Error, TEXT("Propeller curve table does not have %s"), DATA_MOTORTORQUE_NAME);
	}
}

FVector AMotor::CalcTorques() {
	auto torqueAtPowerLeveL = torqueByPowerCurve->Eval(currentPowerLevel); // look up in a table the torque given current power level [0,1] 
	return FVector{ 0,0, 1 } *torqueAtPowerLeveL;
}

void AMotor::PropagateSpeed(float power) {
	assert(childPropeller != nullptr);
	currentPowerLevel = power;
	childPropeller->SetRotationSpeed(currentPowerLevel);		// TODO: make motors configurable
}
