// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowling/UI/PowerBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPowerBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!OwnerBall.IsValid())
	{ 
		return;
	}


	PowerBar->SetPercent(OwnerBall->GetCurrentForce() / OwnerBall->GetMaxForce());

	FNumberFormattingOptions Options;

	// We assume that we just show percentage 0-100
	Options.SetMaximumFractionalDigits(0);
	CurrentPowerLabel->SetText(FText::AsNumber((OwnerBall->GetCurrentForce() / OwnerBall->GetMaxForce()) * 100, &Options));
	MaxPowerLabel->SetText(FText::AsNumber(100, &Options));
}
