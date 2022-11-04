// (c) 2021 MVFT. All Rights Reserved.

#include "Pilot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
APilot::APilot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	collision->InitCapsuleSize(50, 200);	// a bit fat, but should work
	RootComponent = collision;

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetRelativeLocation(FVector(0, 0, 136)); // the camera goes into the head
	camera->SetupAttachment(collision);

}

// Called when the game starts or when spawned
void APilot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APilot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// look at the drone
	if (!UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled()) {
		camera->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Drone->GetActorLocation()));
	}
}

// Called to bind functionality to input
void APilot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// find the drone in the world 
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADrone::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0) {
		Drone = Cast<ADrone>(FoundActors[0]);
	}
	else {
		checkf(false, TEXT("Scene must contain an object of subclass ADrone!"));
	}

	/*PlayerInputComponent->BindAxis("Power", this, &APilot::Power);
	PlayerInputComponent->BindAxis("Forward", this, &APilot::Forward);
	PlayerInputComponent->BindAxis("Right", this, &APilot::Right);
	PlayerInputComponent->BindAxis("RotateZ", this, &APilot::RotateZ);
	PlayerInputComponent->BindAxis("Bank", this, &APilot::SetBank);
	PlayerInputComponent->BindAxis("Pitch", this, &APilot::SetPitch);
	PlayerInputComponent->BindAction("ResetPlane", EInputEvent::IE_Pressed, this, &APilot::ResetPlane);*/
	PlayerInputComponent->BindAction("ToggleHMD", EInputEvent::IE_Pressed, this, &APilot::ToggleHMD);
	PlayerInputComponent->BindAction("SwitchMode", EInputEvent::IE_Pressed, this, &APilot::Switch);
}

void APilot::ToggleHMD() {
	UHeadMountedDisplayFunctionLibrary::EnableHMD(!UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled());
}