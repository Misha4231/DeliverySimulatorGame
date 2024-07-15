// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreensRouting.h"
#include "Blueprint/UserWidget.h"
#include "WeatherScreen.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UWeatherScreen : public UUserWidget, public IScreenRoutingInterface
{
	GENERATED_BODY()

public:
	virtual void SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate);
protected:
	FScreenChangeDelegate ScreenChangeDelegate;
};
