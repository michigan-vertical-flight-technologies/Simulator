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

	FVector PartUpVector() {
		return FVector{ 0,0,1 };
	}
	FVector PartRightVector() {
		return FVector{ 0,1,0 };
	}
	FVector PartForwardVector() {
		return FVector{ 1,0,0 };
	}

	static constexpr float ForceScaleFactor = 10000;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	@return the forces to apply to the base, in part-local space, override in subclasses
	*/
	virtual FVector CalcForces() {
		return FVector(0,0,0);
	}

	/**
	@return the torques to apply to the base, in part-local space, override in subclasses
	*/
	virtual FVector CalcTorques() {
		return FVector(0, 0, 0);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Propeller Parameters")
		float massKg = 1;

};
