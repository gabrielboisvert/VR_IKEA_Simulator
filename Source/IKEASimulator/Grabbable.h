#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/SceneComponent.h"
#include "Grabbable.generated.h"


UINTERFACE(MinimalAPI)
class UGrabbable : public UInterface
{
	GENERATED_BODY()
};


class IKEASIMULATOR_API IGrabbable
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Attach(USceneComponent* hand);

	virtual void Attach_Implementation(USceneComponent* hand) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Detach();

	virtual void Detach_Implementation() = 0;
};
