// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LeBrutalistePlatForm.generated.h"

/**
 * 
 */
UCLASS()
class LEBRUTALISTE_API ALeBrutalistePlatForm : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* PlatFormMesh;
};
