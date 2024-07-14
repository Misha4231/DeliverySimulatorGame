// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePlayerController.h"

void ACorePlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UCoreHUD>(this, HUDBlueprintClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "HUD Created wrongly");
	}
	
}

void ACorePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("GetPhone", IE_Pressed, this, &ACorePlayerController::OnPhoneOpen);
		InputComponent->BindAction("HidePhone", IE_Pressed, this, &ACorePlayerController::OnPhoneClose);
	}
}

void ACorePlayerController::OnPhoneOpen()
{
	if (HUDWidget)
	{
		HUDWidget->GetInPhone();
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "HUD Widget not found");
	}
}

void ACorePlayerController::OnPhoneClose()
{
	if (HUDWidget)
	{
		HUDWidget->HidePhone();
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "HUD Widget not found");
	}
}
