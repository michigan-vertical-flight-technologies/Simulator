// (c) 2021 MVFT. All Rights Reserved.


#include "Motor.h"
#include <cassert>

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
}

FVector AMotor::CalcTorques() {
	float torqueAtPowerLeveL = 0;
	return FVector{ 0,0, 1 } *torqueAtPowerLeveL;	//TODO: look up in a table the power level [0,1] given current RPM
}

// Called every frame
void AMotor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMotor::PropagateSpeed(float power) {
	assert(childPropeller != nullptr);
	childPropeller->SetRotationSpeed(power);		// TODO: make motors configurable
}
