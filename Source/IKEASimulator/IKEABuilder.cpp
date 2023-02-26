#include "IKEABuilder.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Grabbable.h"
#include "Tool.h"


AIKEABuilder::AIKEABuilder()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	PrimaryActorTick.bCanEverTick = true;

	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(RootComponent);

	LeftHandSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandSK"));
	LeftHandSK->SetupAttachment(LeftHand);



	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RootComponent);

	RightHandSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandSK"));
	RightHandSK->SetupAttachment(RightHand);
}

void AIKEABuilder::BeginPlay()
{
	Super::BeginPlay();
}

void AIKEABuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AIKEABuilder::SetupPlayerInputComponent(UInputComponent* pPlayerInputComponent)
{
	check(pPlayerInputComponent);

	PlayerInputComponent = pPlayerInputComponent;
	
	PlayerInputComponent->BindAction<FGrabInput>("LeftGripEnable", IE_Pressed, this, &AIKEABuilder::TryGrab, LeftHandSK, LeftHand, &LeftObjectGrab, ActiveHand::LeftH);
	PlayerInputComponent->BindAction<FGrabInput>("RightGripEnable", IE_Pressed, this, &AIKEABuilder::TryGrab, RightHandSK, RightHand, &RightObjectGrab, ActiveHand::RightH);
	

	PlayerInputComponent->BindAction<FOneParamActor>("LeftGripEnable", IE_Released, this, &AIKEABuilder::Release, &LeftObjectGrab);
	PlayerInputComponent->BindAction<FOneParamActor>("RightGripEnable", IE_Released, this, &AIKEABuilder::Release, &RightObjectGrab);
}

void AIKEABuilder::TryGrab(USkeletalMeshComponent* HandMesh, UMotionControllerComponent* hand, AActor** grab, const ActiveHand E_Hand)
{
	FHitResult hit;
	if (!UKismetSystemLibrary::BoxTraceSingle(
		this,
		HandMesh->GetComponentLocation() + (HandMesh->GetForwardVector() * 6),
		HandMesh->GetComponentLocation() + (HandMesh->GetForwardVector() * 6),
		FVector(2, 2, 2),
		FRotator(0, 0, 0),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::Type::None,
		hit,
		true
	))
	return;

	if (!UKismetSystemLibrary::IsValid(hit.GetActor()))
		return;

	if (!hit.GetActor()->GetClass()->ImplementsInterface(UGrabbable::StaticClass()))
		return;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayHapticEffect(HapticEffect, (hand == LeftHand ? EControllerHand::Left : EControllerHand::Right));

	ATool* tool = Cast<ATool>(hit.GetActor());
	if (tool != nullptr)
		tool->EnableInput(PlayerInputComponent, E_Hand);

	IGrabbable::Execute_Attach(hit.GetActor(), hand);
	*grab = hit.GetActor();
}

void AIKEABuilder::Release(AActor** ObjectGrab)
{
	if (*ObjectGrab == nullptr)
		return;

	ATool* tool = Cast<ATool>(*ObjectGrab);
	if (tool != nullptr)
		tool->DisableInput(PlayerInputComponent);

	IGrabbable::Execute_Detach(*ObjectGrab);
	*ObjectGrab = nullptr;
}