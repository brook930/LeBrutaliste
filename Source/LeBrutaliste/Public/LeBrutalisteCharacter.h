// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "engine.h"
#include "LeBrutalisteScore.h"
#include "LeBrutalisteDestructibleObject.h"
#include "LeBrutalisteController.h"
#include "LeBrutalisteCharacter.generated.h"

UCLASS(config=Game)
class ALeBrutalisteCharacter : public ACharacter
{
	GENERATED_BODY()


	float baseSlamRadius;

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	/** Box that defines the reach of Howard's fists */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HWD_armReach;

	/** Box that defines the reach of Howard's fists */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HWD_slamReach;



	/** Check if the Player is already throwing object **/
	bool hasAlreadyThrow;

	float timerDead;

	/* Last Checkpoint */
	UPROPERTY()
	FVector lastCheckpoint;

protected:

	// CLEAN
	// Override of Tick to move the character
	virtual void Tick(float DeltaSeconds) override;
	
	// Override of BeginPlay to set variables
	virtual void BeginPlay() override;

	virtual void OnLanded(const FHitResult& Hit);


	// MOVE TO DESTRUCTIBLE
	// Iterates on overlapping Green destructible component and destroy them
	//void Hit(short int BoxVal);
	void Hit();

	// CLEAN AND MAYBE MOVE SOME STUFF TO DESTRUCTIBLE
	// Slam function
	void Slam();

	// CLEAN AND MAYBE MOVE SOME STUFF TO DESTRUCTIBLE
	// Throw front objects
	void Throw();

public:

	// ------------------------------------------------------- Variables -------------------------------------------------------


		// ---- Unreal Engine usable ----


			// --- Gameplay ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Gameplay)
	// Choice between running to the left and running to the right
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Gameplay)
	// Choice between running to the left and running to the right
	bool RunsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Gameplay)
	// Choice between running to the left and running to the right
	float JumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Gameplay)
	// Delay between hits
	float HittingDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Gameplay)
	// Delay between throws
	float ThrowingDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Gameplay)
	// Slam Speed. (significant order of magnitude is 1000+)
	float SlammingSpeed;


			// --- Camera ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Camera)
	// Choice between running to the left and running to the right
	float Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Camera)
	// Choice between running to the left and running to the right
	float OffsetX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Camera)
	// Choice between running to the left and running to the right
	float OffsetY;


			// --- Animation ---

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isHitting;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isSuperHitting;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isHittingNothing;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isWrongHitting;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isThrowing;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	bool isSlamming;

	UPROPERTY(BlueprintReadWrite, Category = Le_Brutaliste_Anim)
	float deadAnimationTime;


			// --- Scoring ---
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Scoring)
	//stores the score
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Scoring)
	//stores the build points
	int32 BuildPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Scoring)
	//stores the score last checkpoint
	int32 ScoreCheckpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Scoring)
	//stores the build points last checkpoint
	int32 BuildPointsCheckpoint;


			// --- Test ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Test)
	float timeToFadeHeadScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Test)
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Test)
	// 
	bool stopCharacter;


			// --- Maps ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Maps)
	TArray<FString> PackageNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Maps)
	int32 mapUnlocked;



	// ------------------------------------------------------- Public Functions -------------------------------------------------------


		// ---- Unreal Engine usable ---

	UFUNCTION(BlueprintCallable, Category = "Maps")
	FString GetCurrentMapName();

	UFUNCTION(BlueprintCallable, Category = "Maps")
	FString GetNextMapName();

	UFUNCTION(BlueprintImplementableEvent, Category = LeBrutaliste_Scoring)
	void objectDestroyed(Type objectType, bool destroyed);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }


		// ---- C++ only ----

	// Constructor
	ALeBrutalisteCharacter(const FObjectInitializer& ObjectInitializer);

	// Updates the score (TEST)
	void UpdateScore();

	// Set the position of last Checkpoint
	void SetLastCheckpoint(const FVector NewPosition){ lastCheckpoint = NewPosition; }

	// return the lastCheckpoint position
	FVector GetLastCheckpoint(){ return lastCheckpoint; }

	void getInput(TouchType inputType);

	void tapManager(uint8 NbOfFingerOnScreen);

	void SwipeManager();
};
