// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FlightControllerBase.h"
#include "DebugFlightController.generated.h"

/**
 * 
 */
UCLASS()
class PTRAIN_API ADebugFlightController : public AFlightControllerBase
{
	GENERATED_BODY()

private:
	TArray<AServo*> allServos;
	TArray<AMotor*> allMotors;
public:
	virtual void RegisterMotor(AMotor*) override;
	virtual void RegisterServo(AServo*) override;
	virtual void Switch() override;
};
