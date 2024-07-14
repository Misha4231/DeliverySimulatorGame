// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

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
	bInPhone = true;
	
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
	if (!bInPhone) return;
	if (HUDWidget)
	{
		HUDWidget->HidePhone();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "HUD Widget not found");
	}

	bInPhone = false;
}
