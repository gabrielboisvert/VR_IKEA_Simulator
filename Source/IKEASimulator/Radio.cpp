#include "Radio.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"

// Sets default values
ARadio::ARadio()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARadio::BeginPlay()
{
	Super::BeginPlay();
	this->PlaySound();
	AudioComp->OnAudioFinished.AddDynamic(this, &ARadio::PlaySound);
}

// Called every frame
void ARadio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARadio::PlaySound()
{
	if (Songs.Num() == 0)
		return;

	SongIdx = (SongIdx + 1) % Songs.Num();
	AudioComp->SetSound(Songs[SongIdx]);

	if (!AudioComp->OnAudioPlaybackPercent.Contains(this, "OnAudioPlaybackPercent"))
		AudioComp->OnAudioPlaybackPercent.AddDynamic(this, &ARadio::OnAudioPlaybackPercent);

	AudioComp->FadeIn(FadeDuration, VolumeMultiplier);
}

void ARadio::OnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
	if (PlaybackPercent >= FadeOutPercentage && PlayingSoundWave->GetName().Equals(Songs[SongIdx]->GetName()))
	{
		AudioComp->OnAudioPlaybackPercent.RemoveDynamic(this, &ARadio::OnAudioPlaybackPercent);
		AudioComp->FadeOut(FadeDuration, 0);
	}
}