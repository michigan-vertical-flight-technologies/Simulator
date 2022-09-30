// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "StaticPart.generated.h"

UCLASS()
class PTRAIN_API AStaticPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector WorldUpVector() {
		return GetParentComponent()->GetUpVector();
	}

	FVector WorldForwardVector() {
		return GetParentComponent()->GetForwardVector();
	}

	FVector WorldLocation() {
		return GetParentComponent()->GetComponentLocation();
	}

	FVector LocalSpaceVelocityVector() {
		auto parent = GetParentComponent();
		return UKismetMathLibrary::InverseTransformDirection(parent->GetComponentTransform(), parent->GetComponentVelocity());
	}

	static constexpr float ForceScaleFactor = 10000;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	@return the forces to apply to the base, override in subclasses
	*/
	virtual FVector CalcForces() {
		return FVector(0,0,0);
	}

	/**
	@return the torques to apply to the base, override in subclasses
	*/
	virtual FVector CalcTorques(const FVector& droneRootPos) {
		return FVector(0, 0, 0);
	}

};
