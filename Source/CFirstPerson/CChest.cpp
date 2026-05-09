// Fill out your copyright notice in the Description page of Project Settings.


#include "CChest.h"


// Sets default values
ACChest::ACChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeMeshAsset.Succeeded())
	{	
		CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
		CubeMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	
	



}

// Called when the game starts or when spawned
void ACChest::BeginPlay()
{
	Super::BeginPlay();
	ChestMaterial();

}

// Called every frame
void ACChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACChest::IAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Chest implement intergace"));
	
	switch (ChestState)
	{
	case EChestState::ECS_None:
		{
			UE_LOG(LogTemp, Warning, TEXT("Chest ECS_None"));
			break;
		}
	case EChestState::ECS_Opened:
		{
			UE_LOG(LogTemp, Warning, TEXT("Chest ECS_Opened"));
			ChestState=EChestState::ECS_Closed;
			ChestMaterial();
			break;
		}
	case EChestState::ECS_Closed:
		{
			UE_LOG(LogTemp, Warning, TEXT("Chest ECS_Closed"));	
			ChestState=EChestState::ECS_Opened;
			ChestMaterial();
			break;
		}
		case EChestState::ECS_Blocked:
		{
			UE_LOG(LogTemp, Warning, TEXT("Chest ECS_Blocked"));
			break;
		}
	default:
		{
			UE_LOG(LogTemp, Warning, TEXT("Chest ????"));
		}
	}
}

void ACChest::ChestMaterial()
{
	switch (ChestState)
	{
	case EChestState::ECS_None:
		{
			break;
		}
	case EChestState::ECS_Opened:
		{
			if (OpenMaterial)
			{
				CubeMesh->SetMaterial(0, OpenMaterial); 
			}
			break;
		}
	case EChestState::ECS_Closed:
		{
			
			if (CloseMaterial)
			{
				CubeMesh->SetMaterial(0, CloseMaterial); 
			}
			break;
		}
	case EChestState::ECS_Blocked:
		{
			if (BlockMaterial)
			{
				CubeMesh->SetMaterial(0, BlockMaterial); 
			}
			break;
		}
	default:
		{
			
		}
	}
}

