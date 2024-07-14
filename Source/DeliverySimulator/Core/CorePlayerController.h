// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeliverySimulator/UI/CoreHUD.h"
#include "GameFramework/PlayerController.h"
#include "CorePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UCoreHUD> HUDBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UCoreHUD* HUDWidget;

	UFUNCTION(BlueprintCallable, Category="UI Phone")
	void OnPhoneOpen();

	UFUNCTION(BlueprintCallable, Category="UI Phone")
	void OnPhoneClose();
	
};
