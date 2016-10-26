// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/UMG/Public/UMG.h"
#include "SlateBasics.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "LeBrutalistePauseTutorial.generated.h"

/**
 * 
 */
UCLASS()
class LEBRUTALISTE_API ALeBrutalistePauseTutorial : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = TriggerBox)
	class UBoxComponent* TriggerBox;

	UFUNCTION()
	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UUserWidget> widgetTemplate;

	//UPROPERTY()
	//class UUserWidget* widgetInstance;

	// Image of tutorial
	UPROPERTY(EditInstanceOnly, Category = textureImage)
	class UTexture2D* textureImage;

	// Has the pause already been triggered
	UPROPERTY()
	bool alreadyUsed;

	UFUNCTION(BlueprintImplementableEvent, Category = LeBrutaliste_Pause_Tutorial)
	void widgetCreation(class UTexture2D* texture);

	ALeBrutalistePauseTutorial(const FObjectInitializer& ObjectInitializer);
};
