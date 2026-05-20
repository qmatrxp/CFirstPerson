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

// UENUM()
// enum class EChestShapes : uint8
// {
// 	ECS_None UMETA(DisplayName = "None"),
// 	ECS_Sphere_Empty UMETA(DisplayName = "Sphere Empty"),
// 	ECS_Sphere UMETA(DisplayName = "Sphere"),
// 	ECS_Disk UMETA(DisplayName = "Disk"),
// 	ECS_Cube UMETA(DisplayName = "Cube"),
// 	ECS_Bublik UMETA(DisplayName = "Bublik"),
// 	
// };



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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	bool bSphere_Empty;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Sphere_Empty", meta=(EditCondition="bSphere_Empty", EditConditionHides))
	float fSphere_Empty_Radius =100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Sphere_Empty", meta=(EditCondition="bSphere_Empty", EditConditionHides))
	FColor ColorPixel_Sphere_Empty = FColor::Blue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Sphere_Empty", meta=(EditCondition="bSphere_Empty", EditConditionHides))
	float RadiusPixel_Sphere_Empty = 10.0f;     
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	bool bSphere;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Sphere", meta=(EditCondition="bSphere", EditConditionHides))
	float fSphere_Radius =100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Sphere", meta=(EditCondition="bSphere", EditConditionHides))
	FColor ColorPixel_Sphere = FColor::Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Sphere", meta=(EditCondition="bSphere", EditConditionHides))
	float RadiusPixel_Sphere = 10.0f;     
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	bool bDisk;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Disk", meta=(EditCondition="bDisk", EditConditionHides))
	float fDisk_Radius_One =100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Disk", meta=(EditCondition="bDisk", EditConditionHides))
	float fDisk_Radius_Two =100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Disk", meta=(EditCondition="bDisk", EditConditionHides))
	FColor ColorPixel_Disk = FColor::Green;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Disk", meta=(EditCondition="bDisk", EditConditionHides))
	float RadiusPixel_Disk = 10.0f;  	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	bool bCube;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Cube", meta=(EditCondition="bCube", EditConditionHides))
	float fCube_Length =100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Cube", meta=(EditCondition="bCube", EditConditionHides))
	FColor ColorPixel_Cube = FColor::Cyan;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Cube", meta=(EditCondition="bCube", EditConditionHides))
	float RadiusPixel_Cube = 10.0f;  	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	bool bBublik;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Bublik", meta=(EditCondition="bBublik", EditConditionHides))
	float fBublik_Radius_One =200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Bublik", meta=(EditCondition="bBublik", EditConditionHides))
	float fBublik_Radius_Two =50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Bublik", meta=(EditCondition="bBublik", EditConditionHides))
	FColor ColorPixel_Bublik = FColor::Orange;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes|Bublik", meta=(EditCondition="bBublik", EditConditionHides))
	float RadiusPixel_Bublik = 10.0f; 	
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	// FColor ColorPixel = FColor::Blue;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shapes")
	// float RadiusPixel = 10.0f;     
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void IAction() override;
	void  ChestMaterial();
	
	FChestDelegate ChestDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing="On_RepChestState")
	EChestState ChestState;
	
private:
	void GenerateShapes();
	UFUNCTION()
	void On_RepChestState();
	
	
};
