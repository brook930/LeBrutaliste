// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "LebrutalisteController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum TouchType{
	TAP				UMETA(DisplayName = "Tap"),
	SWIPE			UMETA(DisplayName = "Swipe"),
	DEFAULT
};

UENUM(BlueprintType)
enum SwipeType{
	UPWARDS			UMETA(DisplayName = "Upwards"),
	DOWNWARDS		UMETA(DisplayName = "Downwards"),
	RIGHT			UMETA(DisplayName = "Right"),
	LEFT			UMETA(DisplayName = "Left"),
	SWIPE_ERROR		UMETA(DisplayName = "Swipe_Error")
};

UCLASS()
class LEBRUTALISTE_API ALeBrutalisteController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	// ------------------------------------------------------- Private functions -------------------------------------------------------

private :

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch repeat event. */
	void TouchRepeat(const ETouchIndex::Type FingerIndex, const FVector Location);

	// Calls big hit for keyboard input
	void BigHit();

	// APawn interface
	virtual void SetupInputComponent() override;

	// Override of BeginPlay to set variables
	virtual void BeginPlay() override;

	// Manage input for hit or throw
	void InputManager();

	// Tells if an offset between start and present location of a finger is a swipe
	bool isSwipe();

	void UpdateFingerPos(FVector newPresentLocation);


	// ------------------------------------------------------- Public functions -------------------------------------------------------

public :

	UFUNCTION(BlueprintCallable, Category = "Input")
	// When called, other inputs won't fire
	void ConsumeInput();

	// When called, other inputs won't fire
	void BlockInput();

	// When called, other inputs will fire
	void AllowInput();


	uint8 getNbFingerOnScreen();

	// Decides if swipe is up, down or right
	SwipeType SwipeHandler();

//	ALeBrutalisteController(const FObjectInitializer& ObjectInitializer);


	// ------------------------------------------------------- Variables -------------------------------------------------------

private :

		// ---- C++ Only ----

	// Storage for the position of a finger when it presses the screen
	FVector fingerStart;
	FVector fingerPresentLocation;
	FVector swipeVector;

	uint8 nbOfFingerOnScreen;

	bool inputConsumed;
	bool inputAvailable;

	TouchType touchType;

	bool fingers[2];

		// ---- Unreal Engine usable ----

public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Le_Brutaliste_Characteristics)
	// Minimal length of a swipe to activate a functionality
	float SwipeLength;

};
