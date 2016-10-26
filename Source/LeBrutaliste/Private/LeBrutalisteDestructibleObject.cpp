// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteDestructibleObject.h"
#include "LeBrutalisteCharacter.h"

ALeBrutalisteDestructibleObject::ALeBrutalisteDestructibleObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerBoxComponent"));
	SkeletalMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkeletalMeshComponent"));
	
	SkeletalMesh->AttachTo(RootComponent);
	TriggerBox->AttachTo(SkeletalMesh);

	isDestroyed = false;
	isThrown = false;
	timeCounter = 0.0f;
	timeUntilDestroyed = 10.0f;

	// Throw variables
	pushForce = 1000.0f;
	downForce = 750.0f;
	pushTime = 1.5f;
	isThrowable = true;

	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh->SetCastShadow(false);
}
void ALeBrutalisteDestructibleObject::ReceiveActorBeginOverlap(AActor * OtherActor)
{

	if (!isThrown)
	{
		ALeBrutalisteCharacter* Howard = Cast<ALeBrutalisteCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		ALeBrutalisteDestructibleObject* DestructibleObject = Cast<ALeBrutalisteDestructibleObject>(OtherActor);

		if (DestructibleObject && !this->isDestroyed && !(this->GetType() == Type::RED))
		{
			ALeBrutalisteScore::Gain("scorePoints", DestructibleObject->GetThrownScore());
			ALeBrutalisteScore::Gain("scoreBuildPoints", DestructibleObject->GetThrownBP());
			Howard->objectDestroyed(DestructibleObject->GetType(), DestructibleObject->isDestroyed);
			Howard->UpdateScore();
			isDestroyed = true;
		}
		else if (DestructibleObject && !this->isDestroyed && (this->GetType() == Type::RED))
		{
			ALeBrutalisteScore::Gain("scorePoints", this->GetScore());
			ALeBrutalisteScore::Gain("scoreBuildPoints", this->GetBPValue());
			Howard->objectDestroyed(DestructibleObject->GetType(), DestructibleObject->isDestroyed);
			Howard->UpdateScore();
			isDestroyed = true;
		}



	}	
}

bool ALeBrutalisteDestructibleObject::TestIfDestroyed()
{

	ALeBrutalisteCharacter* Howard = Cast<ALeBrutalisteCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	int32 nbFingerOnscreen = (Cast<ALeBrutalisteController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))->getNbFingerOnScreen();

	if (isDestroyed)
	{
		Howard->isHittingNothing = true;
		return false;
	}

	if ((nbFingerOnscreen == 1 && (GetType() == Type::YELLOW))
		|| (nbFingerOnscreen == 2 && (GetType() == Type::GREEN)))
	{
		Howard->isWrongHitting = true;
		return false; 
	}

	// if the cast is successful then destroy that object
	if ((nbFingerOnscreen == 1) && (GetType() == Type::GREEN || GetType() == Type::SPECIAL || GetType() == Type::RED))
	{
		Howard->isHitting = true;
		ALeBrutalisteScore::Gain("scorePoints", GetScore());
		ALeBrutalisteScore::Gain("scoreBuildPoints", GetBPValue());
		Howard->objectDestroyed(GetType(), isDestroyed);
		isDestroyed = true;
		Howard->UpdateScore();
		return true;
	}

	// if the cast is successful then destroy that object
	if (nbFingerOnscreen == 2 && (GetType() == Type::YELLOW || GetType() == Type::RED || GetType() == Type::SPECIAL))
	{
		Howard->isSuperHitting = true;
		ALeBrutalisteScore::Gain("scorePoints", GetScore());
		ALeBrutalisteScore::Gain("scoreBuildPoints", GetBPValue());
		Howard->objectDestroyed(GetType(), isDestroyed);
		isDestroyed = true;
		Howard->UpdateScore();
		return true;
	}
	return false;
}

void ALeBrutalisteDestructibleObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isDestroyed || isThrown)
	{
		UAnimInstance* animation = SkeletalMesh->GetAnimInstance();
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
		else if (isThrown && animInstance && isThrowable)
		{
			animInstance->isThrown = true;
			ThrowMyself(DeltaSeconds);
		}
	}
}

void ALeBrutalisteDestructibleObject::ThrowMyself(float DeltaSeconds)
{
	//Uncomment to see the line trace on debug
	//const FName TraceTag("MyTraceTag");
	//GetWorld()->DebugDrawTraceTag = TraceTag;

	FCollisionQueryParams traceParams(FName(TEXT("Trace")), true, NULL);
	traceParams.bTraceComplex = true;
	traceParams.bTraceAsyncScene = true;
	traceParams.bReturnPhysicalMaterial = false;

	//traceParams.TraceTag = TraceTag;

	//Ignore Actors
	//TraceParams.AddIgnoredActor(ActorToIgnore);

	FHitResult outHit(ForceInit);
	FVector startLine = SkeletalMesh->GetComponentLocation() + FVector(0, 0, 30);
	FVector endLine = startLine + FVector(0, 0, -20);

	SkeletalMesh->GetWorld()->LineTraceSingle(outHit, startLine, endLine, ECC_Pawn, traceParams);

	tempDownForce = downForce;

	if (outHit.bBlockingHit)
	{
		tempDownForce = 0;
	}

	if (timeCounter <= pushTime || (timeCounter >= pushTime && !outHit.bBlockingHit))
	{
		SkeletalMesh->AddLocalTransform(FTransform(FRotator(0, 0, 0), FVector(0, -(pushForce*DeltaSeconds)*(1 - (timeCounter / pushTime)), -(tempDownForce*DeltaSeconds)), FVector(1, 1, 1)), false);
	}
}

int32 ALeBrutalisteDestructibleObject::GetScore()
{
	if (!isDestroyed && !isThrown)
	{
		return scoreValue;
	}
	else
		return 0;
}

int32 ALeBrutalisteDestructibleObject::GetBPValue()
{
	if (!isDestroyed && !isThrown)
	{
		return buildPointValue;
	}
	else
		return 0;
}

int32 ALeBrutalisteDestructibleObject::GetThrownScore()
{
	if (!isDestroyed)
		return scoreValue;
	else
		return 0;
}

int32 ALeBrutalisteDestructibleObject::GetThrownBP()
{
	if (!isDestroyed)
		return buildPointValue;
	else
		return 0;
}

Type ALeBrutalisteDestructibleObject::GetType()
{
	return myType;
}