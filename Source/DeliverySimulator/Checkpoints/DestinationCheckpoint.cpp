// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationCheckpoint.h"
#include "DeliverySimulator/Core/MainGameInstance.h"
#include "DeliverySimulator/Character/ThirdPersonCharacter.h"

void ADestinationCheckpoint::OnCollisionEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionEnter(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AThirdPersonCharacter *Character = Cast<AThirdPersonCharacter>(OtherActor);
	if (!Character)
		return;

	UMainGameInstance *GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (GameInstance && GameInstance->OrdersSubsystem) {
		FOrder &CurrentOrder = GameInstance->OrdersSubsystem->GetCurrentOrder();

		if (CurrentOrder.Destination.Id == Id && CurrentOrder.State == OrderState::PoductsTaken) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Products are delivered, Congratulations!");

			GameInstance->StatsSubsystem->GiveMoney(CurrentOrder.CalculateEarningsFloat());
			GameInstance->OrdersSubsystem->SetCurrentOrderState(OrderState::NotTaken);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Enter Destination checkpoint");
}

void ADestinationCheckpoint::OnCollisionExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionExit(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Exit Destination checkpoint");
}
