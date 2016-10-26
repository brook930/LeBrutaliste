// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteCheckpoint.h"


ALeBrutalisteCheckpoint::ALeBrutalisteCheckpoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerBoxComponent"));
	SkeletalMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkeletalMeshComponent"));

	TriggerBox->AttachTo(RootComponent);
	SkeletalMesh->AttachTo(RootComponent);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALeBrutalisteCheckpoint::TriggerEnter);

}

void ALeBrutalisteCheckpoint::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	//Check if the checkpoint collide with Howard ("HWD_slamReach") and not is arm ("HWD_armReach")
	if (Cast<ALeBrutalisteCharacter>(OtherActor) && OtherComp->GetName().Equals("Howard's Slam Reach"))
	{
		ALeBrutalisteCharacter* Player = Cast<ALeBrutalisteCharacter>(OtherActor);

		Player->SetLastCheckpoint(this->GetActorLocation() + FVector(0,0,67));
		
		/*FVector BLABLA = Player->GetLastCheckpoint();
		FString bite = BLABLA.ToString();
		DEBUGLOG(bite);*/
	}
}

