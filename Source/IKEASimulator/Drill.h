#pragma once

#include "CoreMinimal.h"
#include "Tool.h"
#include "Delegates/Delegate.h"
#include "Drill.generated.h"

enum RotationType
{
	LeftRt = -1,
	RightRt = 1
};

DECLARE_DELEGATE_TwoParams(FActiveInput, const bool, const enum ActiveHand);
DECLARE_DELEGATE_OneParam(FOneParamInt, const RotationType);

UCLASS()
class IKEASIMULATOR_API ADrill : public ATool
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USphereComponent* HeadTrigger;

	UPROPERTY(EditAnywhere)
	class AScrew* head;

	RotationType HeadRotation = RotationType::RightRt;
	bool bIsActive = false;

	enum ActiveHand currentHand;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float RotationSpeed = 10;

	ADrill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Attach_Implementation(USceneComponent* hand) override;
	virtual void Detach_Implementation() override;

	void Activate(bool bShouldRun, const enum ActiveHand hand);
	void SwitchRotation(const RotationType Rotation);

	void EnableInput(class UInputComponent* pPlayerInputComponent, const enum ActiveHand hand) override;
	void DisableInput(class UInputComponent* pPlayerInputComponent) override;
};
