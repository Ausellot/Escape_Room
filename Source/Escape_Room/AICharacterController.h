// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API AAICharacterController : public AAIController
{
	GENERATED_BODY()

public:
	AAICharacterController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* Pawn) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual FRotator GetControlRotation() const override;

	UFUNCTION()
	void onPawnDetected(const TArray<AActor*> &DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float LoseAISightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	bool bIsPlayerDetected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float DistanceToPlayer = 0.0f;
};
