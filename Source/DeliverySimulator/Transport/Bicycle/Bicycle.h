// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Vehicle.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bicycle.generated.h"

class AThirdPersonCharacter;

USTRUCT(BlueprintType)
struct FBikePoints
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Points")
	FVector Seat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Points")
	FVector LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Points")
	FVector RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Points")
	FVector LeftPedal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Points")
	FVector RightPedal;

	FBikePoints() {}
	
	FBikePoints(const FVector& InSeat, const FVector& InLeftHand, const FVector& InRightHand, 
						 const FVector& InLeftPedal, const FVector& InRightPedal);
};

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API ABicycle : public AVehicle
{
	GENERATED_BODY()

public:
	//  Constructor
	ABicycle();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
public:
	void GetOut(const FInputActionValue &Value) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Cyclist")
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Cyclist")
	UBoxComponent* GetIntoBoxCollision;
	
	UFUNCTION(BlueprintCallable, Category="Cyclist")
	FBikePoints GetBikePoints() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation")
	UAnimMontage* GetOutOfBicycleMontage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation")
	bool bMirrorAnimations = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AThirdPersonCharacter> CharacterClass;
private:
	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	bool SideRayCast(const FVector& Direction) const;
	
	FTimerHandle GetOutOfBicycleHandle;

	UFUNCTION()
	void PossessCharacter(AThirdPersonCharacter* Character);
};
