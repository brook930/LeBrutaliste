// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LeBrutalisteAnimInstance.h"
#include "LeBrutalisteDestructibleObject.generated.h"



/**
 * 
 */
UENUM(BlueprintType)
enum class Type : uint8{
	GREEN			UMETA(DisplayName= "Green"),
	YELLOW			UMETA(DisplayName= "Yellow"),
	RED				UMETA(DisplayName= "Red"),
	SPECIAL			UMETA(DisplayName= "Special"),
	DEATHBOX		UMETA(DisplayName = "Deathbox")
};


UCLASS()
class LEBRUTALISTE_API ALeBrutalisteDestructibleObject : public AActor
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = TriggerBox)
		class UBoxComponent* TriggerBox;

		UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
		class USceneComponent* SceneComponent;
	
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* SkeletalMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Animation)
		TEnumAsByte< EAnimationMode::Type > AnimationMode;

		// Editable Variables
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		int32 hitpoints;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		int32 scoreValue;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		int32 buildPointValue;

		float timeCounter;
		float tempDownForce;

		// Type
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Type)
		Type myType;

	protected:

		// Override of Tick to update animations
		virtual void Tick(float DeltaSeconds) override;
		
		// Throw function
		void ThrowMyself(float DeltaSeconds);

		//Call when BeginOverlap
		virtual void ReceiveActorBeginOverlap(AActor * OtherActor);
		

	public:
		
		bool TestIfDestroyed();

		//score getter
		int32 GetScore();

		//build points getter
		int32 GetBPValue();

		// Type getter
		Type GetType();

		// tell if this destructible is destroyed by a hit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Status)
		bool isDestroyed;

		// tell if this destructible is thrown by the player
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Status)
		bool isThrown;

		// Increase this value to increase the push force of Howard
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		float pushForce;

		// Increase this value to increase the down force when the object is falling
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		float downForce;

		// Increase this value to increase the duration of the push
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		float pushTime;

		// Increase this value to increase the time a destructible can stay alive ingame
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		float timeUntilDestroyed;

		// Tells if the Destructible can be Thrown
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Values)
		bool isThrowable;

	private:
		//getters dedicated to throw WARNING: ONLY FOR THROWN OBJECTS
		int32 GetThrownScore();
		int32 GetThrownBP();
};
