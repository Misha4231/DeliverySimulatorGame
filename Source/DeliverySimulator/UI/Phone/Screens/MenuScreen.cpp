// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuScreen.h"

void UMenuScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate)
{
	ScreenChangeDelegate = InScreenChangeDelegate;
}

void UMenuScreen::NativeConstruct()
{
	Super::NativeConstruct();

	CacheButtons();
}

void UMenuScreen::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMenuScreen::CacheButtons()
{
	for (UWidget* IconWidget : MenuIcons->GetAllChildren())
	{
		UPhoneMenuIcon* Icon = Cast<UPhoneMenuIcon>(IconWidget);
		MenuButtons.Add(Icon);

		Icon->MenuScreenObject = this;
		Icon->OnChangeScreen = &UMenuScreen::ChangeScreen;
	}
}

void UMenuScreen::ChangeScreen(TSubclassOf<UUserWidget> NewScreen)
{
	if (ScreenChangeDelegate.IsBound())
	{
		ScreenChangeDelegate.Execute(NewScreen);
	}
}
