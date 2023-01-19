// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDO.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BDOManager.generated.h"

UCLASS()
class IFOG_API ABDOManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Spawn and manage the location of BDOs.
	ABDOManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Spawn BDO
	ACharacter* SpawnActor();

public:
	// Player reference
	UPROPERTY(EditDefaultsOnly)
	APawn* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BDO)
	UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BDO)
	float BoxX = 5000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BDO)
	float BoxY = 5000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BDO)
	float BoxZ = 2000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BDO)
	TArray<ABDO*> BDOs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BDO)
	TSubclassOf<ACharacter> ActorClassToSpawn;
};
