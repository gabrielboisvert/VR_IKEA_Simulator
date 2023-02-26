#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grabbable.h"
#include "Tool.generated.h"

UCLASS()
class IKEASIMULATOR_API ATool : public AActor, public IGrabbable
{
	GENERATED_BODY()

	
public:	
	ATool();

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Model;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Attach(USceneComponent* hand);

	virtual void Attach_Implementation(USceneComponent* hand) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Detach();

	virtual void Detach_Implementation() override;

	virtual void EnableInput(class UInputComponent* pPlayerInputComponent, const enum ActiveHand hand) {};
	virtual void DisableInput(class UInputComponent* pPlayerInputComponent) {};
};