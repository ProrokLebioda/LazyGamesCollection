// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowling/UI/PowerBarWidget.h"
#include "Components/ProgressBar.h"
#include "Bowling/Player/BowlingBall.h"
#include "Components/TextBlock.h"

void UPowerBarWidget::SetOwner(APlayerController* NewOwner)
{
	if (NewOwner)
	{
		if (ABowlingBall* NewOwnerBall = Cast<ABowlingBall>(NewOwner->GetPawn()))
		{
			SetOwnerBall(NewOwnerBall);
		}
	}
}

void UPowerBarWidget::SetOwnerBall(ABowlingBall* NewOwner)
{
	 //OwnerBall = NewOwner;
	 MaxForce = NewOwner->GetMaxForce();

	 // Bind delegates
	 NewOwner->OnLaunchPowerChange.AddUObject(this, &UPowerBarWidget::UpdatePowerBarValue);
	 NewOwner->OnLaunchStart.AddLambda([this]() {SetVisibility(ESlateVisibility::Visible); });
	 NewOwner->OnLaunchEnd.AddLambda([this]() {SetVisibility(ESlateVisibility::Hidden); });
}


void UPowerBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPowerBarWidget::UpdatePowerBarValue(double Value)
{
	PowerBar->SetPercent(Value / MaxForce);

	FNumberFormattingOptions Options;

	// We assume that we just show percentage 0-100
	Options.SetMaximumFractionalDigits(0);
	CurrentPowerLabel->SetText(FText::AsNumber((Value / MaxForce) * 100, &Options));
	MaxPowerLabel->SetText(FText::AsNumber(100, &Options));
}
