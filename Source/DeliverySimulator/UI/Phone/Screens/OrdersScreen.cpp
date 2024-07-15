// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersScreen.h"

void UOrdersScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate)
{
	ScreenChangeDelegate = InScreenChangeDelegate;
}
