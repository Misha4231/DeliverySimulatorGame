// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Vehicle.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API AVehicle : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	

public:
	AVehicle();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent *CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent *Camera;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
	virtual void DestroyVehicleInput();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext *VehicleMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *HandBrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *GetOutAction;

	void Ride(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandBrake(const FInputActionValue& Value);
	void virtual GetOut(const FInputActionValue &Value){};

public:
	UFUNCTION(BlueprintCallable)
	float GetYRideAxis() const;
private:
	struct FEnhancedInputActionValueBinding* RideActionBinding;
};
