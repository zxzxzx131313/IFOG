// Fill out your copyright notice in the Description page of Project Settings.


#include "BDOManager.h"
#include "GameFramework/Character.h"
#include "Misc/DateTime.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABDOManager::ABDOManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>("SpawnBox");
	RootComponent = SpawnBox;
	ActorClassToSpawn = ABDO::StaticClass();
}

// Called when the game starts or when spawned
void ABDOManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetFirstPlayerController())
	{
		PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	if (SpawnBox)
	{
		SpawnBox->SetBoxExtent(FVector(BoxX, BoxY, BoxZ));
	}
}

// Called every frame
void ABDOManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ACharacter* ABDOManager::SpawnActor()
{
	int signX = FMath::CeilToInt(FMath::FRand()*10)%2==0 ? 1 : -1;
	int signY =  FMath::CeilToInt(FMath::FRand()*10)%2==0 ? -1 : 1;
	FVector SpawnLocation = PlayerRef->GetActorLocation();
	SpawnLocation.X +=  signX * ( 2 * BoxX + BoxX * FMath::FRand());
	SpawnLocation.Y +=  signY * ( 2 * BoxY + BoxY * FMath::FRand());
	SpawnLocation.Z +=  BoxZ * FMath::FRand();

	ABDO* SpawnedBDO = (ABDO*)GetWorld()->SpawnActor(ActorClassToSpawn, &SpawnLocation);

	if (SpawnedBDO)
	{
		BDOs.Add(SpawnedBDO);
	}

	return SpawnedBDO;
}
