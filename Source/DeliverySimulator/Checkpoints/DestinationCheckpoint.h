// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckpointBase.h"
#include "DestinationCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API ADestinationCheckpoint : public ACheckpointBase
{
	GENERATED_BODY()

		
protected:
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
