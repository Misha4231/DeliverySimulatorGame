// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantCheckpoint.h"
#include "DeliverySimulator/Core/MainGameInstance.h"
#include "DeliverySimulator/Character/ThirdPersonCharacter.h"

ARestaurantCheckpoint::ARestaurantCheckpoint()
{
	
}

void ARestaurantCheckpoint::OnCollisionEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionEnter(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AThirdPersonCharacter *Character = Cast<AThirdPersonCharacter>(OtherActor);
	if (!Character)
		return;

	UMainGameInstance *GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (GameInstance && GameInstance->OrdersSubsystem) {
		FOrder &CurrentOrder = GameInstance->OrdersSubsystem->GetCurrentOrder();

		if (CurrentOrder.Restaurant.Id == Id) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Products are taken");
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Enter Restaurant checkpoint");
}

void ARestaurantCheckpoint::OnCollisionExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionExit(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Exit Restaurant checkpoint");
}
