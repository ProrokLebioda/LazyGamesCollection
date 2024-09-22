// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowling/Actors/Ball.h"
#include "Ball.h"
#include "Logging/LogMacros.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::BallDestroyed()
{
	UE_LOG(LogTemp, Warning, TEXT("PICKME UP"));
	this->Destroy();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

