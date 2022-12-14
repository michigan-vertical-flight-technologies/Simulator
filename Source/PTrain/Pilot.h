// (c) 2021 MVFT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Drone.h"
#include "Pilot.generated.h"

UCLASS()
class PTRAIN_API APilot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APilot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ADrone* Drone = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCapsuleComponent* collision;

	void ToggleHMD();

	void Switch(){
		Drone->activeFlightController->Switch();
	}
};
