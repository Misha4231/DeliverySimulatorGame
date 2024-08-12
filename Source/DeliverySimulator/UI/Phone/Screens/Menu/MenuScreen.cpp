// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuScreen.h"



void UMenuScreen::CacheButtons()
{
	for (UWidget* IconWidget : MenuIcons->GetAllChildren())
	{
		UPhoneMenuIcon* Icon = Cast<UPhoneMenuIcon>(IconWidget);
		MenuButtons.Add(Icon);

		Icon->ScreenChangeDelegate = ScreenChangeDelegate;
	}
}

void UMenuScreen::ScreenConstruct()
{
	CacheButtons();
}
