#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Screw.generated.h"

UCLASS()
class IKEASIMULATOR_API AScrew : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Model;

public:	
	AScrew();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};