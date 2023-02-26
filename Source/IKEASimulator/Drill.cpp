#include "Drill.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Screw.h"
#include "IKEABuilder.h"

ADrill::ADrill() : ATool()
{
	HeadTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("HeadTrigger"));
	HeadTrigger->SetupAttachment(this->Model);
}

void ADrill::BeginPlay()
{
	Super::BeginPlay();
}

void ADrill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->bIsActive || this->head == nullptr)
		return;

	this->head->AddActorLocalRotation(FRotator(RotationSpeed * DeltaTime * HeadRotation, 0, 0));
}

void ADrill::Detach_Implementation()
{
	Super::Detach_Implementation();
}

void ADrill::Attach_Implementation(USceneComponent* hand)
{
	Super::Attach_Implementation(hand);
}

void ADrill::Activate(bool bShouldRun, const enum ActiveHand hand)
{
	if (currentHand != hand)
		return;

	this->bIsActive = bShouldRun;
}

void ADrill::SwitchRotation(const RotationType Rotation)
{
	HeadRotation = Rotation;
}

void ADrill::EnableInput(UInputComponent* pPlayerInputComponent, const ActiveHand hand)
{
	currentHand = hand;

	pPlayerInputComponent->BindAction<FActiveInput>("DrillRunLeft", IE_Pressed, this, &ADrill::Activate, true, ActiveHand::LeftH);
	pPlayerInputComponent->BindAction<FActiveInput>("DrillRunLeft", IE_Released, this, &ADrill::Activate, false, ActiveHand::LeftH);

	pPlayerInputComponent->BindAction<FActiveInput>("DrillRunRight", IE_Pressed, this, &ADrill::Activate, true, ActiveHand::RightH);
	pPlayerInputComponent->BindAction<FActiveInput>("DrillRunRight", IE_Released, this, &ADrill::Activate, false, ActiveHand::RightH);

	pPlayerInputComponent->BindAction<FOneParamInt>("Drill/LeftRotation", IE_Pressed, this, &ADrill::SwitchRotation, RotationType::LeftRt);
	pPlayerInputComponent->BindAction<FOneParamInt>("Drill/RightRotation", IE_Pressed, this, &ADrill::SwitchRotation, RotationType::RightRt);
}


void ADrill::DisableInput(UInputComponent* pPlayerInputComponent)
{
	pPlayerInputComponent->RemoveActionBinding("DrillRunLeft", IE_Pressed);
	pPlayerInputComponent->RemoveActionBinding("DrillRunLeft", IE_Released);

	pPlayerInputComponent->RemoveActionBinding("DrillRunRight", IE_Pressed);
	pPlayerInputComponent->RemoveActionBinding("DrillRunRight", IE_Released);

	pPlayerInputComponent->RemoveActionBinding("Drill/LeftRotation", IE_Pressed);
	pPlayerInputComponent->RemoveActionBinding("Drill/RightRotation", IE_Pressed);
}