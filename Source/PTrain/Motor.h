// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Propeller.h"
#include "Motor.generated.h"

UCLASS()
class PTRAIN_API AMotor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMotor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APropeller* childPropeller = nullptr;
	FSimpleCurve* torqueByPowerCurve = nullptr;
	float currentPowerLevel = 0;
public:	

	UPROPERTY(EditAnywhere, Category = "Motor Data")
		class UCurveTable* torqueByPowerLookupTable;

	virtual void PropagateSpeed(float powerLevel);

	virtual FVector CalcTorques();
};
