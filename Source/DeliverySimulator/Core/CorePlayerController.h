// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeliverySimulator/UI/CoreHUD.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CorePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
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

protected:
	UPROPERTY(BlueprintReadOnly, Category="UI Phone")
	bool bInPhone = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* ControllerInputContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* PhoneAction;

	void OnPhoneAction(const FInputActionValue &Value);
};
