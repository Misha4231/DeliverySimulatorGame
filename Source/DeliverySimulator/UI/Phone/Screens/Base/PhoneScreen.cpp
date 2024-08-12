// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneScreen.h"

void UPhoneScreen::SetScreenChangeDelegate(FScreenChangeDelegate* InScreenChangeDelegate, FChangeToCreatedScreenDelegate* InChangeToCreatedScreenDelegate)
{
    ScreenChangeDelegate = InScreenChangeDelegate;
    ChangeToCreatedScreenDelegate = InChangeToCreatedScreenDelegate;

    ScreenConstruct();
}

void UPhoneScreen::ScreenConstruct()
{
}
