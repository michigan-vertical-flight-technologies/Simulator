// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StaticPart.h"
#include "Propeller.generated.h"

/**
 * 
 */
UCLASS()
class PTRAIN_API APropeller : public AStaticPart
{
	GENERATED_BODY()

private:
	float currentRotationSpeed = 0;	// rotation speed is a float from 0 to 1, where 0 is off and 1 is the maximum speed
	FVector prevTickAngularMomentum = FVector{ 0,0,0 };
	float prevTickTime = 0;
public:
	virtual FVector CalcForces() override;
	virtual FVector CalcTorques() override;

	UPROPERTY(EditAnywhere, Category = "Propeller Data")
		class UDataTable* thrustLookupTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Propeller Parameters")
		float momentOfInertia = 0;

	virtual void Tick(float DeltaTime) override;
	
	// invoked by connected Motors
	void SetRotationSpeed(decltype(currentRotationSpeed) r) { currentRotationSpeed = r; }
};
