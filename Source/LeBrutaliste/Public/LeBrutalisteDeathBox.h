// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LeBrutalisteDestructibleObject.h"
#include "LeBrutalisteDeathBox.generated.h"

/**
 * 
 */
UENUM()
enum class DeathboxType : uint8{
	INDESTRUCTIBLE,
	DESTRUCTIBLEBYHIT,
	DESTRUCTIBLEBYTHROW
};

UCLASS()
class LEBRUTALISTE_API ALeBrutalisteDeathBox : public AActor
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditInstanceOnly, Category = Mesh)
	class USkeletalMeshComponent* DeathMeshSkeletal;

	UPROPERTY(EditInstanceOnly, Category = Mesh)
	class UStaticMeshComponent* DeathMeshStatic;

	UPROPERTY(EditInstanceOnly, Category = TriggerBox)
	class UBoxComponent* DeathTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Animation)
	TEnumAsByte< EAnimationMode::Type > AnimationMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Properties)
	bool isDestroyed;


	// Points lost when being killed by this deathbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Properties)
		int32 pointsLost;

	// Build points lost when being killed by this deathbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Properties)
		int32 buildPointsLost;

	// Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Type)
		DeathboxType destructionMode;
	
	// Type getter
		DeathboxType GetType();

		//returns deathbox so when a deathbox is destroyed we can send a type
		Type getGlobalType()
		{
			return Type::DEATHBOX;
		};

		float timeCounter;

public:

	// Increase this value to increase the time a destructible can stay alive ingame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
	float timeUntilDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isGroundDeathBox;

private :

	virtual void ReceiveActorBeginOverlap(AActor* OtherActor);

	void Resurrect(AActor* character);

protected:
	// Override of Tick to update animations
	virtual void Tick(float DeltaSeconds) override;
};
