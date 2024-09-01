// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlowingText.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UGlowingText : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
};
