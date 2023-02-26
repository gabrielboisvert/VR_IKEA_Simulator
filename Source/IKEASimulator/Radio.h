// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Radio.generated.h"

UCLASS()
class IKEASIMULATOR_API ARadio : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Music)
	class UAudioComponent* AudioComp;
	
	UPROPERTY(EditAnywhere, Category = Music)
	TArray<class USoundWave*> Songs;
	unsigned int SongIdx = -1;
	

	UPROPERTY(EditAnywhere, Category = Music)
	float VolumeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Category = Music)
	float FadeDuration = 10;

	UPROPERTY(EditAnywhere, Category = Music)
	float FadeOutPercentage = 0.95f;

public:	
	ARadio();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PlaySound();

	UFUNCTION()
	void OnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, const float PlaybackPercent);
};
