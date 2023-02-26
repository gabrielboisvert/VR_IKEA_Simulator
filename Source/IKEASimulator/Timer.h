// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <chrono>
#include <string>
#include "Timer.generated.h"

UCLASS()
class IKEASIMULATOR_API ATimer : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Time)
	unsigned int TimeMax = 20;

	unsigned int TimeMs;

	UPROPERTY(EditAnywhere, Category = Time)
	class UTextRenderComponent* text;

public:	
	// Sets default values for this actor's properties
	ATimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	std::string FormatDuration(std::chrono::milliseconds ms);
};
