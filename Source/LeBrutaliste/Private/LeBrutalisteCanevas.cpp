// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteCanevas.h"
#include "LeBrutalisteScore.h"

ALeBrutalisteCanevas::ALeBrutalisteCanevas(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	CanevasTriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CanevasTriggerBox"));
	CanevasMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CanevasMesh"));
	CanevasActivationTriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CanevasActivationTriggerBox"));

	ItemToInstantiate = NULL;
	isWrapped = true;

	RootComponent = SceneComponent;
	CanevasTriggerBox->AttachTo(RootComponent);
	CanevasMesh->AttachTo(RootComponent);
	CanevasActivationTriggerBox->AttachTo(RootComponent);

	CanevasMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CanevasMesh->SetCastShadow(false);

	CanevasActivationTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALeBrutalisteCanevas::TriggerEnter);
	CanevasActivationTriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALeBrutalisteCanevas::TriggerExit);
}

void ALeBrutalisteCanevas::ReceiveActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)
{
	FVector position = this->GetActorLocation();

	ALeBrutalisteCharacter* Howard = Cast<ALeBrutalisteCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Howard)
	{
		Cast<ALeBrutalisteController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ConsumeInput();
		if (priceToPay <= ALeBrutalisteScore::GetScore("scoreBuildPoints") && !isWrapped)
		{
			if (ItemToInstantiate != NULL)
				GetWorld()->SpawnActor(ItemToInstantiate, &position);

			ALeBrutalisteScore::Gain("scoreBuildPoints", -priceToPay);
			Howard->UpdateScore();

			this->Destroy();
		}
	}
}

void ALeBrutalisteCanevas::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UAnimInstance* animation = CanevasMesh->GetAnimInstance();
	ULeBrutalisteAnimInstance* animInstance = Cast<ULeBrutalisteAnimInstance>(animation);

	if (animInstance && Cast<ALeBrutalisteCharacter>(OtherActor) && ALeBrutalisteScore::GetScore("scoreBuildPoints") >= priceToPay)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, TEXT("TRIGGER ENTER"));
		isWrapped = false;
		animInstance->CanevasOpen = true;
	}
}

void ALeBrutalisteCanevas::TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	UAnimInstance* animation = CanevasMesh->GetAnimInstance();
	ULeBrutalisteAnimInstance* animInstance = Cast<ULeBrutalisteAnimInstance>(animation);

	if (animInstance && Cast<ALeBrutalisteCharacter>(OtherActor) && !isWrapped)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, TEXT("TRIGGER EXIT"));
		isWrapped = true;
		animInstance->CanevasOpen = false;
	}
}