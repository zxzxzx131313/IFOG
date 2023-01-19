// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "BDO.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNearPlayerSignature, float, PlayerFogOpacity);

class USkeletalMeshComponent;
class USceneComponent;

UCLASS(config=Game)
class IFOG_API ABDO : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABDO();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Player reference
	UPROPERTY(EditDefaultsOnly)
	APawn* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinPlayerRange = 30000.0;
	
	UPROPERTY(BlueprintAssignable, Category = "EventDispatcher")
	FOnNearPlayerSignature OnNearPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BDOMesh;

public:
	// Compute distance to player
	float GetDistToPlayer();

private:
	bool IsExitingFromNearRange = false;

	FVector MoveNorm = FVector(0,0,1);

	FVector StartLoc;

	int Speed = 10;

};
