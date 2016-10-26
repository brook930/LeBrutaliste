// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "LeBrutalisteAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEBRUTALISTE_API ULeBrutalisteAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	//	------------------------------------------------------- Variables -------------------------------------------------------

		//	Unreal Engine usable

	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_States)
		// Tells if the actor has been destroyed by a hit
		bool isDestroyed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_States)
		// Tells if the actor has been thrown by the player
		bool isThrown;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_States)
		// Tells if the actor has been thrown by the player
		bool CanevasOpen;
};
