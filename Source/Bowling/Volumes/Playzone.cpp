// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowling/Volumes/Playzone.h"
#include "Bowling/Actors/Ball.h"
#include "Bowling/Player/BowlingBall.h"

// Sets default values
APlayzone::APlayzone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayzone::BeginPlay()
{
	Super::BeginPlay();
	OnActorEndOverlap.AddDynamic(this, &APlayzone::EndOverlap);
}

void APlayzone::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
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
void APlayzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

