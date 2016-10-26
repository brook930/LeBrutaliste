// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LeBrutalisteCharacter.h"
#include "GameFramework/Actor.h"
#include "LeBrutalisteCanevas.generated.h"

/**
 * 
 */
UCLASS()
class LEBRUTALISTE_API ALeBrutalisteCanevas : public AActor
{
	GENERATED_UCLASS_BODY()
	
public :
	UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = Mesh)
	class USkeletalMeshComponent* CanevasMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = TriggerBox)
	class UBoxComponent* CanevasTriggerBox;

	UPROPERTY(EditInstanceOnly, Category = TriggerBox)
	class UBoxComponent* CanevasActivationTriggerBox;

	UPROPERTY(EditInstanceOnly, Category = ItemToInstantiate)
	class UClass* ItemToInstantiate;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isWrapped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Le_Brutaliste_Canevas_Caractristiques")
	int32 priceToPay;

private :
	virtual void ReceiveActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex);

	UFUNCTION()
	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
