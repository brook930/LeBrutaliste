// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LeBrutalisteCharacter.h"
#include "LeBrutalisteCheckpoint.generated.h"

UCLASS()
class LEBRUTALISTE_API ALeBrutalisteCheckpoint : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
	class USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = TriggerBox)
	class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* SkeletalMesh;

	UFUNCTION()
	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	// Howard destruction score
	UPROPERTY()
	int32 Score;
	// Howard construction score
	UPROPERTY()
	int32 BuildPoints;

	ALeBrutalisteCheckpoint(const FObjectInitializer& ObjectInitializer);
};
