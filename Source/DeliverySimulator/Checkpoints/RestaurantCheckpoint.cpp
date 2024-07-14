// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantCheckpoint.h"

ARestaurantCheckpoint::ARestaurantCheckpoint()
{
	
}

void ARestaurantCheckpoint::OnCollisionEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionEnter(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Enter Restaurant checkpoint");
}

void ARestaurantCheckpoint::OnCollisionExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionExit(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Exit Restaurant checkpoint");
}
