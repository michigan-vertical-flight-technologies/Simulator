// (c) 2021 MVFT. All Rights Reserved.


#include "StaticPart.h"

// Sets default values
AStaticPart::AStaticPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStaticPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaticPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

