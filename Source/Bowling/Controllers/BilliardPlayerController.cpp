// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowling/Controllers/BilliardPlayerController.h"
#include "BilliardPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"


ABilliardPlayerController::ABilliardPlayerController()
{

}

void ABilliardPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABilliardPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//// Add Input Mapping Context
	//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	//{
	//	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//}

	//// Set up action bindings
	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	//{
	//	// Setup mouse input events
	//	//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AClaimFrontierPlayerController::OnInputStarted);
	//	//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AClaimFrontierPlayerController::OnSetDestinationTriggered);
	//	//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AClaimFrontierPlayerController::OnSetDestinationReleased);
	//	//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AClaimFrontierPlayerController::OnSetDestinationReleased);

	//	//// Setup touch input events
	//	//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AClaimFrontierPlayerController::OnInputStarted);
	//	//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AClaimFrontierPlayerController::OnTouchTriggered);
	//	//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AClaimFrontierPlayerController::OnTouchReleased);
	//	//EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AClaimFrontierPlayerController::OnTouchReleased);
	//}
}

