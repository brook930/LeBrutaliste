// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LeBrutalisteCharacter.h"
#include "GameFramework/Actor.h"
#include "LeBrutalisteTrampoline.generated.h"

/**
 * 
 */
UCLASS()
class LEBRUTALISTE_API ALeBrutalisteTrampoline : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* TrampolineMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = TriggerBox)
	class UBoxComponent* TrampolineTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Le_Brutaliste_Canevas_Caractéristiques")
	float jumpSpeed;
	
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor);

	virtual void OnConstruction(const FTransform& Transform);

	void IsHowardOverlapping();

	void megaJump(ALeBrutalisteCharacter* Howard);
};
