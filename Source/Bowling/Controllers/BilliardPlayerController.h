// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BilliardPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class BOWLING_API ABilliardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABilliardPlayerController();

	/** Mapping context*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

	///** Called for looking input */
	//void Look(const FInputActionValue& Value);


};
