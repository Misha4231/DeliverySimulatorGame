// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreensRouting.generated.h"


DECLARE_DELEGATE_OneParam(FScreenChangeDelegate, TSubclassOf<UUserWidget>);
DECLARE_DELEGATE_OneParam(FChangeToCreatedScreenDelegate, UUserWidget*);

UINTERFACE(MinimalAPI)
class UScreenRoutingInterface : public UInterface
{
	GENERATED_BODY()
};

class DELIVERYSIMULATOR_API IScreenRoutingInterface
{
	GENERATED_BODY()

public:
	virtual void SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate) = 0;
};


/**
 * 
*/
class DELIVERYSIMULATOR_API ScreensRouting
{
public:
	ScreensRouting();
	~ScreensRouting();
};
