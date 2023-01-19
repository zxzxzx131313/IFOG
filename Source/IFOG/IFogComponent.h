// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "IFogComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class IFOG_API UIFogComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIFogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Fog Bounding Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BoundingBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScaleX = 500.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScaleY = 500.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScaleZ = 100.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpacityVal = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* FogMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* FogMatDynamic;

	UFUNCTION(BlueprintCallable, Category = BoundingBox)
	void UpdateFogOpacity(float Opacity);

	UFUNCTION(BlueprintCallable, Category = BoundingBox)
	float GetOpacity();
	
};


