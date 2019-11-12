// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWaypoint.h"
#include "AICharacter.h"

// Sets default values
AAIWaypoint::AAIWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAIWaypoint::OnPlayerEnter);
}

// Called when the game starts or when spawned
void AAIWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIWaypoint::OnPlayerEnter(UPrimitiveComponent* OverlapComponent,
								AActor* OtherActor,
								UPrimitiveComponent* OtherComponent,
								int32 OtherBodyIndex,
								bool bFromSweep,
								const FHitResult& SweepResult)
{
	AAICharacter* Character = nullptr;

	if (OtherActor != nullptr)
	{
		Character = Cast<AAICharacter>(OtherActor);
		if (Character != nullptr)
		{
			Character->NextWaypoint = NextWaypoint;
		}
	}

}

