// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StaticPart.h"
#include "Motor.h"
#include "FlightControllerBase.h"
#include "Drone.generated.h"

#define BP_CAT "Aircraft Parameters"

UCLASS()
class PTRAIN_API ADrone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float power = 0;
	FVector moveVec;
	bool isHovering = true;	// begin in hover mode 

	FVector startPos;

	TArray<AStaticPart*> allParts;
	TArray<AMotor*> allMotors;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Reset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Aircraft Parameters")
		float ForceScaleFactor = 10000;

	AFlightControllerBase* activeFlightController = nullptr;
};
