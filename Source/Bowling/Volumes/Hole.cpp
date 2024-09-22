// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowling/Volumes/Hole.h"
#include "Bowling/Actors/Ball.h"
#include "Bowling/Player/BowlingBall.h"

// Sets default values
AHole::AHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHole::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AHole::BeginOverlap);
}

void AHole::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor))
	{
		Ball->BallDestroyed();
	}
	else if (auto PlayerBall = Cast<ABowlingBall>(OtherActor))
	{
		PlayerBall->ResetBallPosition();
	}
}

// Called every frame
void AHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

