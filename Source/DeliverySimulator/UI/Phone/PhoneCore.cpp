// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneCore.h"
#include "DeliverySimulator/UI/CoreHUD.h"

void UPhoneCore::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenChangeDelegate.BindUObject(this, &UPhoneCore::ChangeScreen);
	ChangeToCreatedScreenDelegate.BindUObject(this, &UPhoneCore::ChangeToCreatedScreen);
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


void UPhoneCore::ChangeScreen(TSubclassOf<UPhoneScreen> NewScreenClass)
{
	if (ScreensStack.Num() > 1 && NewScreenClass.Get()->GetName() == ScreensStack.Last()->GetClass()->GetName())
		return;
	
	for (UPhoneScreen* Screen : ScreensStack) {
		if (NewScreenClass.Get()->GetName() == Screen->GetClass()->GetName()) {
			while (ScreensStack.Num() > 1 && NewScreenClass.Get()->GetName() != ScreensStack.Last()->GetClass()->GetName()) {
				ScreensStack.Pop();
			}

			ShowCurrentTopScreen();
			return;
		}
	}

	if (UPhoneScreen* NewScreen = CreateWidget<UPhoneScreen>(this, NewScreenClass))
	{
		NewScreen->SetScreenChangeDelegate(&ScreenChangeDelegate, &ChangeToCreatedScreenDelegate);
		
		ScreensStack.Push(NewScreen);
		ShowCurrentTopScreen();
	}
}
void UPhoneCore::ChangeToCreatedScreen(UPhoneScreen* NewScreen) {
	if (!NewScreen || 
		(ScreensStack.Num() > 1 && NewScreen->GetClass()->GetName() == ScreensStack.Last()->GetClass()->GetName())) {
		return;
	}

	for (UPhoneScreen* Screen : ScreensStack) {
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

	NewScreen->SetScreenChangeDelegate(&ScreenChangeDelegate, &ChangeToCreatedScreenDelegate);
}

void UPhoneCore::ShowCurrentTopScreen() {
	if (ScreensStack.Num() >= 1) {
		ScreensWrapper->ClearChildren();
		ScreensWrapper->AddChild(ScreensStack.Last());
		ScreensStack.Last()->ScreenConstruct();
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
