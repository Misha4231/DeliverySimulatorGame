// Fill out your copyright notice in the Description page of Project Settings.


#include "GlowingPipe.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraUIComponent.h"

void UGlowingPipe::NativePreConstruct()
{
    PipeImage->SetBrushTintColor(FSlateColor(TintColor));
    PipeImage->SetDesiredSizeOverride(ParticlesPlaneSize);

    if (GlowingParticles) {
        GlowingParticles->SetDesiredWidgetSize(ParticlesPlaneSize);

        if (UNiagaraUIComponent* NiagaraComponent = GlowingParticles->GetNiagaraComponent()) {
            NiagaraComponent->SetNiagaraVariableLinearColor(FString("Color"), TintColor);

            NiagaraComponent->SetNiagaraVariableFloat(FString("SpriteMinSize"), SpriteMinScale);
            NiagaraComponent->SetNiagaraVariableFloat(FString("SpriteMaxSize"), SpriteMaxScale);

            NiagaraComponent->SetNiagaraVariableFloat(FString("ParticlesCount"), ParticlesCount);

            NiagaraComponent->SetNiagaraVariableVec2(FString("ParticlesMinVelocity"), ParticlesMinVelocity);
            NiagaraComponent->SetNiagaraVariableVec2(FString("ParticlesMaxVelocity"), ParticlesMaxVelocity);
            
            NiagaraComponent->SetNiagaraVariableVec2(FString("ParticlesPlaneSize"), ParticlesPlaneSize);
        }
    }
}
