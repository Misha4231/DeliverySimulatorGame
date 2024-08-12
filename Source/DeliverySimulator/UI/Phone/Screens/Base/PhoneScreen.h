// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/Delegate.h"
#include "PhoneScreen.generated.h"

DECLARE_DELEGATE_OneParam(FScreenChangeDelegate, TSubclassOf<UPhoneScreen>);
DECLARE_DELEGATE_OneParam(FChangeToCreatedScreenDelegate, UPhoneScreen*);

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UPhoneScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetScreenChangeDelegate(FScreenChangeDelegate* InScreenChangeDelegate, FChangeToCreatedScreenDelegate* InChangeToCreatedScreenDelegate);

public:
	virtual void ScreenConstruct();
protected:
	FScreenChangeDelegate* ScreenChangeDelegate;
	FChangeToCreatedScreenDelegate* ChangeToCreatedScreenDelegate;
};
