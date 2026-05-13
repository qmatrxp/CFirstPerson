// Fill out your copyright notice in the Description page of Project Settings.


#include "CChest.h"


// Sets default values
ACChest::ACChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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
	GenerateShapes();
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

void ACChest::GenerateShapes()
{
	FVector SphereCenter = GetActorLocation();

	
	if (bSphere)//Сфера
	{
		//Получаем рандом 2д вектор
		FVector2D FV2Sphere =FMath::RandPointInCircle(fSphere_Radius);
		
		//2д вектор преобразуем в 3д вектор
		FVector FVSphere = FVector(FV2Sphere,0.0f);
	
		// Создаём ротатор  в градусах c рандомом 0..360 1й координаты
		FRotator RotationSphere(FMath::RandRange(0.0f,360.0f), 0.0f, 0.0f);       

		// Поворачиваем вектор и прибавляем координаты актора
		FVector RotatedVectorSphere = RotationSphere.RotateVector(FVSphere)+GetActorLocation();
		
		DrawDebugSphere(GetWorld(), RotatedVectorSphere, RadiusPixel_Sphere, 1, ColorPixel_Sphere, false, 2.0f, 0, 2.0f);
	}
	if (bSphere_Empty)
	{
		//Получаем рандомное направление в 3д, умножаем на радиус и прибавляем координаты актора
		FVector FVSphere_Empty=FMath::VRand()*fSphere_Empty_Radius+GetActorLocation();
		DrawDebugSphere(GetWorld(), FVSphere_Empty, RadiusPixel_Sphere_Empty, 1, ColorPixel_Sphere_Empty, false, 2.0f, 0, 2.0f);
	}
	if (bDisk)
	{
		//Генерируем полоску со смещением от нулевой координаты
		FVector FVDisk = FVector(FMath::RandRange(0.0f,fDisk_Radius_One)+fDisk_Radius_Two,0.0f,0.0f);
		
		//Создаём ротатор  в градусах c рандомом 0..360 
		FRotator RotationDisk(0.0f, FMath::RandRange(0.0f,360.0f), 0.0f);    
		
		// Поворачиваем вектор и прибавляем координаты актора
		FVector RotatedVectorDisk = RotationDisk.RotateVector(FVDisk)+GetActorLocation();
		
		DrawDebugSphere(GetWorld(), RotatedVectorDisk, RadiusPixel_Disk, 1, ColorPixel_Disk, false, 2.0f, 0, 2.0f);
	}
	if (bCube)
	{
		//Генерируем координаты от середины линии
		FVector FVCube = FVector(FMath::RandRange(-fCube_Length/2,fCube_Length/2),FMath::RandRange(-fCube_Length/2,fCube_Length/2),FMath::RandRange(-fCube_Length/2,fCube_Length/2));
		
		DrawDebugSphere(GetWorld(), FVCube+GetActorLocation(), RadiusPixel_Cube, 1, ColorPixel_Cube, false, 2.0f, 0, 2.0f);
	}
	
	if (bBublik)
	{
		//Создаем координату радиуса бублика (первого)
		FVector FVBublik_Radius_One = FVector(fBublik_Radius_One,0.0f,0.0f);
		
		//Создаём ротатор для первого радиуса в градусах c рандомом 0..360 
		FRotator RotationBublikOne(0.0f, FMath::RandRange(0.0f,360.0f), 0.0f);    
		
		// Поворачиваем вектор первого радиуса
		FVector RotatedVectorBublikOne = RotationBublikOne.RotateVector(FVBublik_Radius_One);
		
		//К вектору первого радиуса прибавляем рандом направление умноженную на второй радиус  (сфера)
		FVector RotatedVectorBublikTwo =RotatedVectorBublikOne + FMath::VRand()*fBublik_Radius_Two;
		
		
		
		DrawDebugSphere(GetWorld(), RotatedVectorBublikTwo+GetActorLocation(), RadiusPixel_Bublik, 1, ColorPixel_Bublik, false, 2.0f, 0, 2.0f);

	}
	
	
}

