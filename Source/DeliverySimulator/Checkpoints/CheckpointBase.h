// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "CheckpointBase.generated.h"

UCLASS()
class DELIVERYSIMULATOR_API ACheckpointBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UCapsuleComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* MainMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	FString Name;

protected:
	UFUNCTION()
	virtual void OnCollisionEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){};

	UFUNCTION()
	virtual void OnCollisionExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){};
};
