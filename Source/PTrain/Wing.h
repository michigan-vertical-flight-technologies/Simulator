// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StaticPart.h"
#include "Wing.generated.h"

/**
 * 
 */
UCLASS()
class PTRAIN_API AWing : public AStaticPart
{
	GENERATED_BODY()
protected:
	float CalcLiftForward();
	float CalcDragInline();
	FVector CalcDrag();
	float Falpha(float alpha);
public:
	virtual FVector CalcForces() override;
	virtual FVector CalcTorques() override;

	UPROPERTY(EditAnywhere, Category = "Wing Data")
		class UCurveTable* liftDragByAlpha;

	UPROPERTY(EditAnywhere, Category = "Wing Data")
		float ro = 0;

	UPROPERTY(EditAnywhere, Category = "Wing Data")
		float wingArea = 0;

	UPROPERTY(EditAnywhere, Category = "Wing Data")
		float wingLength = 0;
};
