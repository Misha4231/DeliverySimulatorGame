// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneCore.h"
#include "DeliverySimulator/UI/CoreHUD.h"

void UPhoneCore::NativeConstruct()
{
	Super::NativeConstruct();
	
	for (UWidget* Screen : ScreensSwitcher->GetAllChildren())
	{
		SetPhoneWidget(Screen);
	}

	if (FadeIn) PlayAnimation(FadeIn);
	else GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "FadeInAnimation not found");
}

void UPhoneCore::OnHidePhoneAnimation()
{
	if (FadeOut) PlayAnimation(FadeOut);
	else GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "FadeOutAnimation not found");
}

void UPhoneCore::OnHidePhone()
{
	if (HUD)
	{
		HUD->OverlayPhonePosition->RemoveChild(this);

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		HUD->PhoneWidget = nullptr;
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f,FColor::Red, "HUD not found");
	}
}

void UPhoneCore::SetPhoneWidget(UWidget* Screen)
{
}

void UPhoneCore::ChangeScreen(const int ActiveWidgetIndex)
{
	ScreensSwitcher->SetActiveWidgetIndex(ActiveWidgetIndex);
}
