// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CActionInterface.h"
#include "GameFramework/Actor.h"
#include "CChest.generated.h"


UENUM()
enum class EChestState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Opened UMETA(DisplayName = "Opened"),
	ECS_Closed UMETA(DisplayName = "Closed"),
	ECS_Blocked UMETA(DisplayName = "Blocked")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChestDelegate);

UCLASS()
class CFIRSTPERSON_API ACChest : public AActor, public ICActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACChest();
	UStaticMeshComponent* CubeMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* OpenMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* CloseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* BlockMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void IAction() override;
	void  ChestMaterial();
	
	FChestDelegate ChestDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EChestState ChestState;
};
