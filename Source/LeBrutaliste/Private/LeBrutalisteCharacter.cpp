// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#include "LeBrutaliste.h"
#include "LeBrutalisteCharacter.h"
#include "TimeHandler.h"
#include "LeBrutalisteDeathBox.h"

ALeBrutalisteCharacter::ALeBrutalisteCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	// Maps
	PackageNames.Add(TEXT("StLaurent_Master"));
	PackageNames.Add(TEXT("Beaubien_Master"));
	PackageNames.Add(TEXT("McGill_Master"));
	PackageNames.Add(TEXT("PeelLaFinal"));
	mapUnlocked = 0;

	// By default, Howard runs to the right of the screen
	RunsLeft = false;

	Speed = 600.f;
	JumpHeight = 1000.f;

	Zoom = 500.f;
	OffsetX = 300.f;
	OffsetY = 100.f;

	isHitting = false;
	isSuperHitting = false;
	isWrongHitting = false;
	isThrowing = false;
	isDead = false;
	
	//base slam reach radius
	baseSlamRadius = 60.f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	//CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	//CameraBoom->AttachTo(RootComponent);
	//CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(RootComponent);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	HWD_armReach = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Howard's Arm Reach"));
	HWD_armReach->AttachTo(RootComponent);

	HWD_slamReach = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Howard's Slam Reach"));
	HWD_slamReach->AttachTo(RootComponent);
	HWD_slamReach->SetSphereRadius(baseSlamRadius);

	// Touch parameters
	hasAlreadyThrow = false;

	timerDead = 0.0f;
	deadAnimationTime = 2.0f;

	// Time to super punch
	//TimeForForceAction = 0.2;

	timeToFadeHeadScore = 0.5;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	ALeBrutalisteScore::initScore("scorePoints", 9999999, 0, 0);
	ALeBrutalisteScore::initScore("scoreBuildPoints", 100, 0, 0);
}

void ALeBrutalisteCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!stopCharacter)
	{
		if (RunsLeft)
			AddMovementInput(FVector(0.f, -1.f, 0.f), -1);
		else
			AddMovementInput(FVector(0.f, -1.f, 0.f), 1);
	}
		
	if (isDead && timerDead < deadAnimationTime )
	{
		timerDead += DeltaSeconds;
		stopCharacter = true;

		//Player can't jump or attack when he died
		Cast<ALeBrutalisteController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->BlockInput();

	}
	else
	{
		if (isDead)
		{
			this->SetActorLocation(this->GetLastCheckpoint());
			timerDead = 0;
			stopCharacter = false;

			//Player can jump or attack
			Cast<ALeBrutalisteController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->AllowInput();
		}

		isDead = false;
		//Player can jump or attack
		Cast<ALeBrutalisteController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->AllowInput();

	}

	// hit with one finger start timer
	if ((isHitting || isSuperHitting || isHittingNothing || isWrongHitting) && !TimeHandler::isRunning(Time5))
	{
		TimeHandler::startTimer(Time5);
	}
	else if (TimeHandler::isRunning(Time5) && TimeHandler::isSuperiorTo(Time5, 0.05))
	{
		isHitting = false;
		isSuperHitting = false;
		isHittingNothing = false;
		isWrongHitting = false;
		TimeHandler::StopTimer(Time5);
	}

	if (isThrowing && !TimeHandler::isRunning(Time6))
	{
		TimeHandler::startTimer(Time6);
	}
	else if (TimeHandler::isRunning(Time6) && TimeHandler::isSuperiorTo(Time6, 0.01))
	{
		isThrowing = false;
		TimeHandler::StopTimer(Time6);
	}
}

void ALeBrutalisteCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->JumpZVelocity = JumpHeight;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	ALeBrutalisteScore::ReinitScore("scorePoints");
	ALeBrutalisteScore::ReinitScore("scoreBuildPoints");
}

void ALeBrutalisteCharacter::Hit()
{
	if (TimeHandler::isRunning(Time2))
	{
		if (TimeHandler::isSuperiorTo(Time2, HittingDelay))
			TimeHandler::resetTimer(Time2);
		else
			return;
	}
	else
	{
		TimeHandler::startTimer(Time2);
	}
	
	TArray<AActor*> TouchingActors;
	HWD_armReach->GetOverlappingActors(TouchingActors);

	for (int32 iTouching = 0; iTouching < TouchingActors.Num(); ++iTouching)
	{
		ALeBrutalisteDestructibleObject* DestructibleObject = Cast<ALeBrutalisteDestructibleObject>(TouchingActors[iTouching]);

		if (DestructibleObject)
			DestructibleObject->TestIfDestroyed();

		ALeBrutalisteDeathBox* DeathBox = Cast<ALeBrutalisteDeathBox>(TouchingActors[iTouching]);
		if (DeathBox)
		{
			if (DeathBox->GetType() == DeathboxType::DESTRUCTIBLEBYHIT)
			{
				isHitting = true;
				DeathBox->DeathTriggerBox->DestroyComponent();
				DeathBox->isDestroyed = true;
				break;
			}
		}
	}

	if (!isHitting && !isSuperHitting)
		isHittingNothing = true;

}

void ALeBrutalisteCharacter::Throw()
{

	//timer
	if (TimeHandler::isRunning(Time3))
	{
		if (TimeHandler::isSuperiorTo(Time3, ThrowingDelay))
			TimeHandler::resetTimer(Time3);
		else
			return;
	}
	else
	{
		TimeHandler::startTimer(Time3);
	}

	isThrowing = true;
	TArray<AActor*> TouchingActors;
	HWD_armReach->GetOverlappingActors(TouchingActors);

	for (int32 iTouching = 0; iTouching < TouchingActors.Num(); ++iTouching)
	{
		ALeBrutalisteDestructibleObject* DestructibleObject = Cast<ALeBrutalisteDestructibleObject>(TouchingActors[iTouching]);

		if (DestructibleObject)
		{
			ALeBrutalisteScore::Gain("scorePoints", DestructibleObject->GetScore());
			ALeBrutalisteScore::Gain("scoreBuildPoints", DestructibleObject->GetBPValue());
			objectDestroyed(DestructibleObject->GetType(), DestructibleObject->isDestroyed);
			UpdateScore();
			DestructibleObject->isThrown = true;
			break;
		}
	}
}

void ALeBrutalisteCharacter::Slam()
{
	if (!(this->CanJump()) && !isSlamming)
	{
		if (!TimeHandler::isRunning(Time7))
			TimeHandler::startTimer(Time7);
		else
			TimeHandler::resetTimer(Time7);
		
		isSlamming = true;
		this->LaunchCharacter(FVector(0.f, 0.f, -SlammingSpeed), false, false);
	}
}

void ALeBrutalisteCharacter::OnLanded(const FHitResult& Hit){

	TArray<AActor*> TouchingActors;
	
	if (isSlamming)
	{
		//DEBUGLOGINT(TimeHandler::TimeElapsedInMilliseconds(Time7))
		HWD_slamReach->SetSphereRadius(baseSlamRadius + (TimeHandler::TimeElapsedInMilliseconds(Time7))*1.5);
		HWD_slamReach->GetOverlappingActors(TouchingActors);

		for (int32 iTouching = 0; iTouching < TouchingActors.Num(); ++iTouching)
		{
			ALeBrutalisteDestructibleObject* DestructibleObject = Cast<ALeBrutalisteDestructibleObject>(TouchingActors[iTouching]);

			if (DestructibleObject)
			{
				ALeBrutalisteScore::Gain("scorePoints", DestructibleObject->GetScore());
				ALeBrutalisteScore::Gain("scoreBuildPoints", DestructibleObject->GetBPValue());
				objectDestroyed(DestructibleObject->GetType(), DestructibleObject->isDestroyed);
				DestructibleObject->isDestroyed = true;
				UpdateScore();
			}

		}
		isSlamming = false;
		HWD_slamReach->SetSphereRadius(baseSlamRadius);
	}
}


void ALeBrutalisteCharacter::UpdateScore()
{
	Score = ALeBrutalisteScore::GetScore("scorePoints");
	BuildPoints = ALeBrutalisteScore::GetScore("scoreBuildPoints");
}

FString ALeBrutalisteCharacter::GetCurrentMapName()
{
	UWorld* MyWorld = GetWorld();
	FString CurrentMapName = MyWorld->GetMapName();

	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, TEXT("mapname:" + CurrentMapName));

	//Remove UEDPIE_0_ or UEDPC

	if (CurrentMapName.Contains("UEDPIE_0_"))
	{
		CurrentMapName.RemoveAt(0, 9, true);
	}
	else if (CurrentMapName.Contains("UEDPC"))
	{
		CurrentMapName.RemoveAt(0, 5, true);
	}
	
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, TEXT("after:" + CurrentMapName));

	return CurrentMapName;
}

FString ALeBrutalisteCharacter::GetNextMapName()
{
	FString CurrentMapName = ""; 
	FString NextMapName = "";
	FString MapToLoad = "";

	CurrentMapName = GetCurrentMapName();

	for (int i = 0; i < PackageNames.Num(); i++)
	{
		NextMapName = PackageNames[i];
		//~~~~~~~~~~~~~~~~~~~~~~

		if (NextMapName.Equals(CurrentMapName))
		{
			if (i + 1 < PackageNames.Num())
			{
				MapToLoad = PackageNames[i + 1];
				return MapToLoad;
			}
		}	
	}
	return MapToLoad;
}

void ALeBrutalisteCharacter::getInput(TouchType inputType)
{
	if (inputType == TouchType::TAP)
		Hit();
	else if (inputType == TouchType::SWIPE)
		SwipeManager();
}

void ALeBrutalisteCharacter::SwipeManager()
{
	switch ((Cast<ALeBrutalisteController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))->SwipeHandler())
	{
	case SwipeType::UPWARDS :
		Jump();
		break;
	case SwipeType::DOWNWARDS :
		Slam();
		break;
	case SwipeType::RIGHT :
		Throw();
		break;
	case SwipeType::LEFT :
		break;
	}
}