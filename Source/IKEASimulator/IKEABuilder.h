#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "IKEABuilder.generated.h"

enum ActiveHand
{
	LeftH,
	RightH
};

DECLARE_DELEGATE_OneParam(FOneParamActor, AActor**);
DECLARE_DELEGATE_FourParams(FGrabInput, class USkeletalMeshComponent*, class UMotionControllerComponent*, AActor**, const ActiveHand);

UCLASS()
class IKEASIMULATOR_API AIKEABuilder : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


	UPROPERTY(EditAnywhere, Category = Hand)
	class UMotionControllerComponent* LeftHand;

	UPROPERTY(EditAnywhere, Category = Hand)
	class USkeletalMeshComponent* LeftHandSK;

	UPROPERTY(EditAnywhere, Category = Hand)
	class UMotionControllerComponent* RightHand;

	UPROPERTY(EditAnywhere, Category = Hand)
	class USkeletalMeshComponent* RightHandSK;

	UPROPERTY(EditAnywhere, Category = Hand)
	class UHapticFeedbackEffect_Base* HapticEffect;

	AActor* LeftObjectGrab;
	AActor* RightObjectGrab;
	class UInputComponent* PlayerInputComponent;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hand)
	float LeftGripForce = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hand)
	float RightGripForce = 0;

	AIKEABuilder();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* pPlayerInputComponent) override;

	void TryGrab(class USkeletalMeshComponent* HandMesh, class UMotionControllerComponent* hand, AActor** grab, const ActiveHand E_Hand);
	void Release(AActor** ObjectGrab);
};