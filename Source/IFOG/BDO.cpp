// Fill out your copyright notice in the Description page of Project Settings.


#include "BDO.h"

// Sets default values
ABDO::ABDO()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	BDOMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BDOMesh"));

	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder(
		TEXT("StaticMesh'/Game/Mesh/donut.donut'"));
	if (MeshFinder.Succeeded())
	{
		BDOMesh->SetStaticMesh(MeshFinder.Get());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Load BDO Mesh"));
	}
	BDOMesh->SetupAttachment(GetCapsuleComponent());


}

// Called when the game starts or when spawned
void ABDO::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld()->GetFirstPlayerController())
	{
		PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	}

	StartLoc = GetActorLocation();
	int dirX = FMath::CeilToInt(FMath::FRand()*10)%2==0?1:0;
	int dirY = FMath::CeilToInt(FMath::FRand()*10)%2==0?1:0;
	int dirZ = FMath::CeilToInt(FMath::FRand()*10)%2==0?1:0;
	MoveNorm = FVector(dirX, dirY, dirZ);
	// BDOMesh->SetWorldScale3D(FVector(10.f, 10.f, 10.f));
}

// Called every frame
void ABDO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float Dist = GetDistToPlayer();

	if (Dist < MinPlayerRange)
	{
		// controls the visibility ratio between fog opacity and distance to player

		float OpacityConverted = FMath::Clamp(20.f*FMath::Exp(-4.5*(Dist/10000.f)), 0.0, 1.f);

		OnNearPlayer.Broadcast(OpacityConverted);
		IsExitingFromNearRange = true;
	} else if(IsExitingFromNearRange && Dist >= MinPlayerRange)
	{
		IsExitingFromNearRange = false;

		OnNearPlayer.Broadcast(0.01f);
		
	}

	
}

// Called to bind functionality to input
void ABDO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABDO::GetDistToPlayer()
{
	return GetHorizontalDistanceTo(PlayerRef);
}
