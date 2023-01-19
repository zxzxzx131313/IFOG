// Fill out your copyright notice in the Description page of Project Settings.


#include "IFogComponent.h"

UIFogComponent::UIFogComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> BoxMesh(
		TEXT("StaticMesh'/Game/Mesh/Cube.Cube'"));
	if (BoxMesh.Succeeded())
	{
		// BoundingBox = BoxMesh.Get();
		SetStaticMesh(BoxMesh.Get());
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Load Fog Bounding Box Mesh"));
	}


	static ConstructorHelpers::FObjectFinderOptional<UMaterial> Mat(
		TEXT("Material'/Game/FX/MM_LocalFog.MM_LocalFog'"));

	if (Mat.Succeeded())
	{
		FogMat = Mat.Get();
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Find Fog Material"));
	}

	SetMobility(EComponentMobility::Movable);
}

// Called when the game starts
void UIFogComponent::BeginPlay()
{
	Super::BeginPlay();
	
	FogMatDynamic = UMaterialInstanceDynamic::Create(FogMat, GetStaticMesh());
	SetMaterial(0, FogMatDynamic);
}


// Called every frame
void UIFogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UIFogComponent::UpdateFogOpacity(float Opacity)
{
	FogMatDynamic->SetScalarParameterValue((TEXT("opacity")), Opacity);
	OpacityVal = Opacity;
}


float UIFogComponent::GetOpacity()
{
	return OpacityVal;
}
