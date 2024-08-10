// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "Camera/CameraComponent.h"
#include "DeliverySimulator/Transport/Bicycle/Bicycle.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "AITypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "InputActionValue.h"
#include "ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class DELIVERYSIMULATOR_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// action handled with F to enter transport
	UFUNCTION(Category = "Bicycle")
	void GetOnBicycleAnimation(bool Side);

	// get into bicycle method
	UFUNCTION(Category = "Bicycle")
	void GetOnBicycle();
	
private:
	void OnMoveToBicycleComplete(const bool Side); // left (false) or right (true)
	
	FTimerHandle GetInTransportTimer;
	
protected:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void DestroyCharacterInput();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UAnimMontage* GetOnBicycleMontage;
	
	void HandleEnterBicycleCollision(ABicycle* Bicycle);
	void HandleExitBicycleCollision(ABicycle* Bicycle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bicycle")
	TArray<bool> WalkToBicycleState = {false, false}; // [0] - is walk right now [1] - left (false) or right (true)
private:
	UPROPERTY()
	ABicycle* ClosestBicycle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext *CharacterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction *GetInsideAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue &Value);
	void GetOnBicycleAction(const FInputActionValue &Value);
};
