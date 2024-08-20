// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckpointBase.h"
#include "RestaurantCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API ARestaurantCheckpoint : public ACheckpointBase
{
	GENERATED_BODY()

public:
	ARestaurantCheckpoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TArray<int> AvailableFoodIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UTexture2D* Logo;
	
protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
