#include "Screw.h"
#include "Components/StaticMeshComponent.h"


AScrew::AScrew()
{
	PrimaryActorTick.bCanEverTick = true;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tool"));
	Model->SetupAttachment(RootComponent);
}


void AScrew::BeginPlay()
{
	Super::BeginPlay();
	
}


void AScrew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

