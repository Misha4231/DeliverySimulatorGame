// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreHUD.h"

void UCoreHUD::NativeConstruct()
{
	
}

void UCoreHUD::GetInPhone()
{
	if (!PhoneWidget)
	{
		if (PhoneWidgetBlueprintClass)
		{
			PhoneWidget = CreateWidget<UPhoneCore>(this, PhoneWidgetBlueprintClass, "PhoneWidget");
			PhoneWidget->HUD = this;
			
			OverlayPhonePosition->AddChild(PhoneWidget);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "PhoneWidgetBlueprintClass not found");
		}
	}
}

void UCoreHUD::HidePhone()
{
	if (PhoneWidget)
		PhoneWidget->OnHidePhoneAnimation();
}
