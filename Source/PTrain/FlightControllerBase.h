// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Motor.h"
#include "Servo.h"
#include "GameFramework/Actor.h"
#include "FlightControllerBase.generated.h"

UCLASS()
class PTRAIN_API AFlightControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlightControllerBase();

public:	

	virtual void RegisterMotor(AMotor*) {}
	virtual void RegisterServo(AServo*) {}

	virtual void Switch() {};

};
