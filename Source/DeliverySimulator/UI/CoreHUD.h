// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Phone/PhoneCore.h"
#include "Kismet/GameplayStatics.h"
#include "CoreHUD.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UCoreHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UOverlay* OverlayPhonePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Phone")
	UPhoneCore* PhoneWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Phone")
	TSubclassOf<UPhoneCore> PhoneWidgetBlueprintClass;

	UFUNCTION(BlueprintCallable, Category="Phone")
	void GetInPhone();

	UFUNCTION(BlueprintCallable, Category="Phone")
	void HidePhone();
};
