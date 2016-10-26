// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteTrampoline.h"
#include "LeBrutalisteCharacter.h"

ALeBrutalisteTrampoline::ALeBrutalisteTrampoline(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	TrampolineTriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TrampolineTriggerBox"));
	TrampolineMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TrampolineMesh"));

	RootComponent = SceneComponent;
	TrampolineTriggerBox->AttachTo(RootComponent);
	TrampolineMesh->AttachTo(RootComponent);

	TrampolineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TrampolineMesh->SetCastShadow(false);
}

void ALeBrutalisteTrampoline::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	ALeBrutalisteCharacter* howard = Cast<ALeBrutalisteCharacter>(OtherActor);

	if (howard)
		megaJump(howard);
}

void ALeBrutalisteTrampoline::OnConstruction(const FTransform& Transform)
{

	GetWorldTimerManager().SetTimer(this, &ALeBrutalisteTrampoline::IsHowardOverlapping, 0.01f, false);
		
}

void ALeBrutalisteTrampoline::IsHowardOverlapping()
{
	TArray<AActor*> actorTab;

	GetOverlappingActors(actorTab);

	ALeBrutalisteCharacter* howard;

	for (int i = 0; i < actorTab.Num(); i++)
	{
		howard = Cast<ALeBrutalisteCharacter>(actorTab[i]);

		if (howard)
		{
			megaJump(howard);
			break;
		}
	}
}

void ALeBrutalisteTrampoline::megaJump(ALeBrutalisteCharacter* Howard)
{
	TArray<UPrimitiveComponent*> touchingComponents;
	TrampolineTriggerBox->GetOverlappingComponents(touchingComponents);
	for (uint16 i = 0; i < touchingComponents.Num(); i++)
	{
		UCapsuleComponent* HowardCapsule = Cast<UCapsuleComponent>(touchingComponents[i]);
		if (!Howard->CanJump())
			GetWorldTimerManager().SetTimer(this, &ALeBrutalisteTrampoline::IsHowardOverlapping, 0.1f, false);
		else if (HowardCapsule)
			Howard->LaunchCharacter(FVector(0.f, 0.f, jumpSpeed), false, false);
	}
}