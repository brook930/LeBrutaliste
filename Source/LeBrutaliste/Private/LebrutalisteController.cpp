// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteCharacter.h"
#include "LebrutalisteController.h"
#include <cmath>

ALeBrutalisteController::ALeBrutalisteController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SwipeLength = 100.f;

	// Vectors storing the position of finger on the screen
	fingerStart = FVector(0);
	fingerPresentLocation = FVector(0);
	swipeVector = FVector(0);

	inputConsumed = false;
	inputAvailable = true;

	nbOfFingerOnScreen = 0;

	touchType = TouchType::DEFAULT;
}

void ALeBrutalisteController::SetupInputComponent()
{
	// set up gameplay key bindings

	Super::SetupInputComponent();

	//InputComponent->BindAction("MegaPunch", IE_Pressed, this, &ALeBrutalisteController::BigHit);
	InputComponent->BindTouch(IE_Pressed, this, &ALeBrutalisteController::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ALeBrutalisteController::TouchStopped);
	InputComponent->BindTouch(IE_Repeat, this, &ALeBrutalisteController::TouchRepeat);
}

void ALeBrutalisteController::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{

	if (FingerIndex == ETouchIndex::Touch1)
	{
		fingerStart = Location;
		if (!inputConsumed && !fingers[0])
		{
			nbOfFingerOnScreen++;
			fingers[0] = true;
		}
	}
	else if (FingerIndex == ETouchIndex::Touch2)
	{
		touchType = TouchType::TAP;

		if (!inputConsumed && !fingers[1])
		{
			nbOfFingerOnScreen++;
			fingers[1] = true;
		}

		InputManager();
	}
}

void ALeBrutalisteController::TouchRepeat(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	UpdateFingerPos(Location);
	if (isSwipe())
	{
		touchType = TouchType::SWIPE;
		InputManager();
	}
}

void ALeBrutalisteController::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		if (touchType == TouchType::DEFAULT)
			touchType = TouchType::TAP;
		InputManager();
	}

	if (nbOfFingerOnScreen > 0 && (FingerIndex == ETouchIndex::Touch1 || FingerIndex == ETouchIndex::Touch2))
		nbOfFingerOnScreen--;

	switch (FingerIndex)
	{
	case ETouchIndex::Touch1 :
		fingers[0] = false;
		break;

	case ETouchIndex::Touch2 :
		fingers[1] = false;
		break;
	}

	if (nbOfFingerOnScreen == 0)
	{
		inputConsumed = false;
		touchType = TouchType::DEFAULT;
	}

}

void ALeBrutalisteController::InputManager()
{
	if (!inputConsumed && inputAvailable)
	{
		Cast<ALeBrutalisteCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->getInput(touchType);
	}
}

bool ALeBrutalisteController::isSwipe()
{
	if (fingerPresentLocation == FVector(0) || fingerStart == FVector(0) ||
		nbOfFingerOnScreen != 1 || inputConsumed || !inputAvailable)
		return false;
	else
		return (fingerPresentLocation - fingerStart).Size() > SwipeLength;
}

void ALeBrutalisteController::UpdateFingerPos(FVector newPresentLocation)
{
	fingerPresentLocation = newPresentLocation;

	swipeVector = newPresentLocation - fingerStart;
}

SwipeType ALeBrutalisteController::SwipeHandler()
{
	if (isSwipe())
	{
		if (swipeVector.GetAbs().Y > swipeVector.GetAbs().X)
		{
			if (swipeVector.Y < 0)
				return SwipeType::UPWARDS;
			
			else
				return SwipeType::DOWNWARDS;
		}
		else
		{
			if (swipeVector.GetAbs().Y < swipeVector.GetAbs().X)
			{
				if (swipeVector.X > 0)
					return SwipeType::RIGHT;
				
				else
					return SwipeType::LEFT;
			}
		}
	}

	return SwipeType::SWIPE_ERROR;
}

void ALeBrutalisteController::ConsumeInput()
{
	inputConsumed = true;
	nbOfFingerOnScreen = 0;
}

void ALeBrutalisteController::BlockInput()
{
	inputAvailable = false;
}

void ALeBrutalisteController::AllowInput()
{
	inputAvailable = true;
}

uint8 ALeBrutalisteController::getNbFingerOnScreen()
{
	return nbOfFingerOnScreen;
}

void ALeBrutalisteController::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(this);
}