// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerBarWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOWLING_API UPowerBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetOwner(APlayerController* NewOwner);
	void SetOwnerBall(class ABowlingBall* NewOwner);

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY( meta = (BindWidget))
	class UProgressBar* PowerBar;

	UPROPERTY( meta = (BindWidget))
	class UTextBlock* CurrentPowerLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxPowerLabel;

private:
	double MaxForce;

private:
	void UpdatePowerBarValue(double Value);

};
