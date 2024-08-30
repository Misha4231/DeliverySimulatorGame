// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "NiagaraSystemWidget.h"
#include "GlowingPipe.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UGlowingPipe : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct();

public:
	UPROPERTY(meta=(BindWidget))
	UImage *PipeImage;

	UPROPERTY(EditAnywhere, Category="Image")
	FLinearColor TintColor;

	UPROPERTY(meta=(BindWidget))
	UNiagaraSystemWidget *GlowingParticles;

	UPROPERTY(EditAnywhere, Category="Particles")
	FVector2D ParticlesPlaneSize;

	UPROPERTY(EditAnywhere, Category="Particles")
	FVector2D ParticlesMinVelocity;

	UPROPERTY(EditAnywhere, Category="Particles")
	FVector2D ParticlesMaxVelocity;

	UPROPERTY(EditAnywhere, Category="Particles")
	float SpriteMinScale;
	
	UPROPERTY(EditAnywhere, Category="Particles")
	float SpriteMaxScale;

	UPROPERTY(EditAnywhere, Category="Particles")
	float ParticlesCount;
};
