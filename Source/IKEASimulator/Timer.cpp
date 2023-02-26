#include "Timer.h"
#include "Components/TextRenderComponent.h"
#include <sstream>


ATimer::ATimer()
{
	PrimaryActorTick.bCanEverTick = true;

	text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("AudioComponent"));
	text->SetupAttachment(RootComponent);
}

void ATimer::BeginPlay()
{
	Super::BeginPlay();
    TimeMs = TimeMax * 60000;
}

void ATimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TimeMs -= DeltaTime * 1000;
    std::string str = FormatDuration(std::chrono::milliseconds(TimeMs));
    FText strText = FText::FromString(str.c_str());
    text->SetText(strText);
}

std::string ATimer::FormatDuration(std::chrono::milliseconds ms) {
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(ms);
    ms -= std::chrono::duration_cast<std::chrono::milliseconds>(secs);
    
    auto mins = std::chrono::duration_cast<std::chrono::minutes>(secs);
    secs -= std::chrono::duration_cast<std::chrono::seconds>(mins);

    std::stringstream ss;
    ss << mins.count() << " : " << (secs.count() < 10? "0" : "") << secs.count();
    
    return ss.str();
}