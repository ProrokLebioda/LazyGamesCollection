// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Bowling/Player/BowlingBall.h"
#include "PowerBarWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOWLING_API UPowerBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerBall(ABowlingBall* NewOwner) { OwnerBall = NewOwner; }

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<ABowlingBall> OwnerBall;

	UPROPERTY( meta = (BindWidget))
	class UProgressBar* PowerBar;

	UPROPERTY( meta = (BindWidget))
	class UTextBlock* CurrentPowerLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxPowerLabel;


};
