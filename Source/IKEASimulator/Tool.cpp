#include "Tool.h"
#include "Components/StaticMeshComponent.h"

ATool::ATool()
{
 	PrimaryActorTick.bCanEverTick = true;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tool"));
	Model->SetupAttachment(RootComponent);
}


void ATool::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATool::Detach_Implementation()
{
	RootComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void ATool::Attach_Implementation(USceneComponent* hand)
{
	this->AttachToComponent(hand, FAttachmentTransformRules::KeepWorldTransform);
}