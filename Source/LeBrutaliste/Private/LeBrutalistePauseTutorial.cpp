// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteCharacter.h"
#include "LeBrutalistePauseTutorial.h"

ALeBrutalistePauseTutorial::ALeBrutalistePauseTutorial(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerBoxComponent"));

	TriggerBox->AttachTo(RootComponent);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALeBrutalistePauseTutorial::TriggerEnter);

	textureImage = NULL;
	alreadyUsed = false;
}

void ALeBrutalistePauseTutorial::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ALeBrutalisteCharacter>(OtherActor) && OtherComp->GetClass() == UCapsuleComponent::StaticClass())
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		if (widgetTemplate)
		{
			//widgetInstance = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), widgetTemplate);

			//widgetInstance->AddToViewport();

			widgetCreation(textureImage);
		}
	}
}


