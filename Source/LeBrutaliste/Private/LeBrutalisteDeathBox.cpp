// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteDeathBox.h"
#include "LeBrutalisteCharacter.h"
#include "LeBrutalisteScore.h"
#include "LeBrutalisteCheckpoint.h"

ALeBrutalisteDeathBox::ALeBrutalisteDeathBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	DeathTriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("DeathTriggerBox"));
	DeathMeshSkeletal = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("DeathMeshSkeletal"));
	DeathMeshStatic = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DeathMeshStatic"));

	DeathTriggerBox->SetBoxExtent(FVector(32.0, 32.0, 75.0), false);
	DeathTriggerBox->SetRelativeLocation(FVector(0.0, 0.0, 75.0));


	RootComponent = SceneComponent;
	DeathTriggerBox->AttachTo(RootComponent);
	DeathMeshSkeletal->AttachTo(RootComponent);
	DeathMeshStatic->AttachTo(RootComponent);

	DeathMeshSkeletal->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DeathMeshSkeletal->SetCastShadow(false);

	DeathMeshStatic->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DeathMeshStatic->SetCastShadow(false);

	DeathTriggerBox->GetCollisionResponseToChannel(ECC_Pawn);

	PrimaryActorTick.bCanEverTick = true;

	timeCounter = 0.0f;
	timeUntilDestroyed = 10.0f;
}


void ALeBrutalisteDeathBox::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	ALeBrutalisteCharacter* Player = Cast<ALeBrutalisteCharacter>(OtherActor);
	
	if (Player) {
		TArray<UPrimitiveComponent*> touchingComponents;
		DeathTriggerBox->GetOverlappingComponents(touchingComponents);
		for (uint16 i = 0; i < touchingComponents.Num(); i++)
		{
			UCapsuleComponent* PlayerCapsule = Cast<UCapsuleComponent>(touchingComponents[i]);
			if (PlayerCapsule)
			{
				//ALeBrutalisteScore::SetScore("scorePoints", Player->ScoreCheckpoint);
				//ALeBrutalisteScore::SetScore("scoreBuildPoints", Player->BuildPointsCheckpoint);
				//Howard->UpdateScore();

					Player->isDead = true;
					Resurrect(PlayerCapsule->GetOwner());

			}
		}

	}


	ALeBrutalisteDestructibleObject* destructibleObject = Cast<ALeBrutalisteDestructibleObject>(OtherActor);
	if (destructibleObject && (this->GetType() == DeathboxType::DESTRUCTIBLEBYTHROW || this->GetType() == DeathboxType::DESTRUCTIBLEBYHIT))
	{
		isDestroyed = true;
		this->DeathTriggerBox->DestroyComponent();
	}
}

void ALeBrutalisteDeathBox::Resurrect(AActor* character)
{
	ALeBrutalisteCharacter* Player = Cast<ALeBrutalisteCharacter>(character);

	//Howard->SetActorLocation(Howard->GetLastCheckpoint());
	ALeBrutalisteScore::Gain("scorePoints", -pointsLost);
	ALeBrutalisteScore::Gain("scoreBuildPoints", -buildPointsLost);
	Player->objectDestroyed(getGlobalType(), isDestroyed);
	Player->UpdateScore();

}

DeathboxType ALeBrutalisteDeathBox::GetType()
{
	return destructionMode;
}

void ALeBrutalisteDeathBox::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isDestroyed)
	{
		if (DeathMeshSkeletal)
		{
			UAnimInstance* animation = DeathMeshSkeletal->GetAnimInstance();

			ULeBrutalisteAnimInstance* animInstance = Cast<ULeBrutalisteAnimInstance>(animation);

			timeCounter += DeltaSeconds;

			if (timeCounter > timeUntilDestroyed)
			{
				this->Destroy();
			}
			if (isDestroyed && animInstance)
			{
				animInstance->isDestroyed = true;
			}
		}
	}
}