// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneCore.h"
#include "DeliverySimulator/UI/CoreHUD.h"
#include "Screens/ScreensRouting.h"

void UPhoneCore::NativeConstruct()
{
	Super::NativeConstruct();

	for (TSubclassOf<UUserWidget>& ScreenClass : ScreenClassesArray)
	{
		UUserWidget* NewScreen = CreateWidget<UUserWidget>(this, ScreenClass);
		if (NewScreen)
		{
			ScreensSwitcher->AddChild(NewScreen);
			ScreensArray.Add(NewScreen);

			if (IScreenRoutingInterface* RoutingInterface = Cast<IScreenRoutingInterface>(NewScreen))
			{
				RoutingInterface->SetScreenChangeDelegate(FScreenChangeDelegate::CreateUObject(this, &UPhoneCore::ChangeScreen));
			}
		}
	}
	
	UpdateBackground();

	BackButton->OnClicked.AddDynamic(this, &UPhoneCore::GoHomeScreen);
	
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


void UPhoneCore::ChangeScreen(const int ActiveWidgetIndex)
{
	if (ScreensSwitcher && ScreensArray.IsValidIndex(ActiveWidgetIndex))
	{
		ScreensSwitcher->SetActiveWidgetIndex(ActiveWidgetIndex);
	}

	UpdateBackground();
}

void UPhoneCore::UpdateBackground()
{
	const int CurrentIndex = ScreensSwitcher->GetActiveWidgetIndex();

	if (CurrentIndex == 0)
	{
		HeaderBackground->SetVisibility(ESlateVisibility::Hidden);
		ScreenSwitcherWrapper->SetBrushColor(FLinearColor::Transparent);
		GoBackSectionWrapper->SetVisibility(ESlateVisibility::Hidden);
	} else
	{
		HeaderBackground->SetVisibility(ESlateVisibility::Visible);
		ScreenSwitcherWrapper->SetBrushColor(FLinearColor::White);
		GoBackSectionWrapper->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPhoneCore::GoHomeScreen()
{
	ChangeScreen(0);
}
