// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneCore.h"
#include "DeliverySimulator/UI/CoreHUD.h"
#include "Screens/ScreensRouting.h"

void UPhoneCore::NativeConstruct()
{
	Super::NativeConstruct();

	
	ChangeScreen(MenuScreenClass);

	BackButton->OnClicked.AddDynamic(this, &UPhoneCore::GoBackScreen);
	
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


void UPhoneCore::ChangeScreen(TSubclassOf<UUserWidget> NewScreenClass)
{
	// if (ScreensStack.Num() > 1) {
	// 	GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Blue, NewScreenClass.Get()->GetName() + FString(" - ") + FString(ScreensStack.Last()->GetClass()->GetName()));
	// }
	
	if (ScreensStack.Num() > 1 && NewScreenClass.Get()->GetName() == ScreensStack.Last()->GetClass()->GetName())
		return;
	
	for (UUserWidget* Screen : ScreensStack) {
		if (NewScreenClass.Get()->GetName() == Screen->GetClass()->GetName()) {
			while (ScreensStack.Num() > 1 && NewScreenClass.Get()->GetName() != ScreensStack.Last()->GetClass()->GetName()) {
				ScreensStack.Pop();
			}

			ShowCurrentTopScreen();
			return;
		}
	}

	if (UUserWidget* NewScreen = CreateWidget<UUserWidget>(this, NewScreenClass))
	{
		ScreensStack.Push(NewScreen);
		ShowCurrentTopScreen();

		if (IScreenRoutingInterface* RoutingInterface = Cast<IScreenRoutingInterface>(ScreensStack.Last()))
		{
			RoutingInterface->SetScreenChangeDelegate(FScreenChangeDelegate::CreateUObject(this, &UPhoneCore::ChangeScreen), FChangeToCreatedScreenDelegate::CreateUObject(this, &UPhoneCore::ChangeToCreatedScreen));
		}
	}
}
void UPhoneCore::ChangeToCreatedScreen(UUserWidget* NewScreen) {
	if (!NewScreen || 
		(ScreensStack.Num() > 1 && NewScreen->GetClass()->GetName() == ScreensStack.Last()->GetClass()->GetName())) {
		return;
	}

	for (UUserWidget* Screen : ScreensStack) {
		if (NewScreen->GetClass()->GetName() == Screen->GetClass()->GetName()) {
			while (ScreensStack.Num() > 1 && NewScreen->GetClass()->GetName() != Screen->GetClass()->GetName()) {
				ScreensStack.Pop();
			}

			ShowCurrentTopScreen();
			return;
		}
	}

	ScreensStack.Push(NewScreen);
	ShowCurrentTopScreen();

	if (IScreenRoutingInterface* RoutingInterface = Cast<IScreenRoutingInterface>(ScreensStack.Last()))
	{
		RoutingInterface->SetScreenChangeDelegate(FScreenChangeDelegate::CreateUObject(this, &UPhoneCore::ChangeScreen), FChangeToCreatedScreenDelegate::CreateUObject(this, &UPhoneCore::ChangeToCreatedScreen));
	}
}

void UPhoneCore::ShowCurrentTopScreen() {
	if (ScreensStack.Num() >= 1) {
		ScreensWrapper->ClearChildren();
		ScreensWrapper->AddChild(ScreensStack.Last());
	}

	UpdateBackground();
}
void UPhoneCore::UpdateBackground()
{
	if (ScreensStack.Num() <= 1)
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
	while (ScreensStack.Num() > 1)
	{
		ScreensStack.Pop();
	}
	ShowCurrentTopScreen();
}

void UPhoneCore::GoBackScreen()
{
	if (ScreensStack.Num() > 1)
	{
		ScreensStack.Pop();
		ShowCurrentTopScreen();
	}
}
