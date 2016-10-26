// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalistePlatForm.h"

ALeBrutalistePlatForm::ALeBrutalistePlatForm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	PlatFormMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PlatFormMesh"));

	RootComponent = SceneComponent;
	PlatFormMesh->AttachTo(RootComponent);

	PlatFormMesh->SetCastShadow(false);
}

