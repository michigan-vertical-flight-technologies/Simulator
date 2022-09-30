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
	float currentRotationSpeed;	// rotation speed is a float from 0 to 1, where 0 is off and 1 is the maximum speed
public:
	virtual FVector CalcForces() override;
	virtual FVector CalcTorques(const FVector& droneRootPos) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Propeller Parameters")
		float PowerFactor = 10;

	virtual void Tick(float DeltaTime) override {
		AddActorLocalRotation(FRotator(0, 20, 0) * currentRotationSpeed);
	}
	
	// invoked by connected Motors
	void SetRotationSpeed(decltype(currentRotationSpeed) r) { currentRotationSpeed = r; }
};
