// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterController.h"
#include "AICharacter.h"
#include "AIWaypoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AAICharacterController::AAICharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = LoseAISightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAICharacterController::onPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

}

void AAICharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("System Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Problem has occured"));
	}
}

void AAICharacterController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);
}

void AAICharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AAICharacter* Character = Cast<AAICharacter>(GetPawn());

	if (DistanceToPlayer > AISightRadius)
	{
		bIsPlayerDetected = false;
	}

	// moves to waypoint
	if (Character->NextWaypoint != nullptr && bIsPlayerDetected == false)
	{
		MoveToActor(Character->NextWaypoint, 5.0f);
	}
	else if (bIsPlayerDetected == true)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MoveToActor(Player, 5.0f);
	}
}

FRotator AAICharacterController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AAICharacterController::onPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for (size_t i = 0; i < DetectedPawns.Num(); i++)
	{
		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);

		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistanceToPlayer);
	}

	bIsPlayerDetected = true;
}
