// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherScreen.h"

void UWeatherScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate)
{
	ScreenChangeDelegate = InScreenChangeDelegate;
}
