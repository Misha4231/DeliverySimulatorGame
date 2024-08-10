// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
        Subsystem->AddMappingContext(ControllerInputContext, 0);
    }
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(PhoneAction, ETriggerEvent::Started, this, &ACorePlayerController::OnPhoneAction);
	}
}

void ACorePlayerController::OnPhoneAction(const FInputActionValue &Value)
{
	const float CurrentValue = Value.Get<float>();

	if (CurrentValue > 0) {
		bInPhone = true;
		if (HUDWidget)
		{
			HUDWidget->GetInPhone();
		} else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "HUD Widget not found");
		}
	} else {
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
}
