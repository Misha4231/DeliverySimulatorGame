// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "MainGameInstance.h"


void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());

	if (!GameInstance) return;
	
	if (RestaurantCheckpointClass)
	{
		TArray<AActor*> FoundRestaurantCheckpoints;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), RestaurantCheckpointClass, FoundRestaurantCheckpoints);

		for (AActor* FoundRestaurantCheckpointActor : FoundRestaurantCheckpoints)
		{
			if (const ARestaurantCheckpoint* RestaurantCheckpoint = Cast<ARestaurantCheckpoint>(FoundRestaurantCheckpointActor))
			{
				FRestaurant NewRestaurant = FRestaurant();
			
				NewRestaurant.Id = RestaurantCheckpoint->Id;
				NewRestaurant.Location = RestaurantCheckpoint->GetActorLocation();
				NewRestaurant.Name = RestaurantCheckpoint->Name;
				NewRestaurant.AvailableFoodIds = RestaurantCheckpoint->AvailableFoodIds;
			
				GameInstance->Restaurants.Add(NewRestaurant);
			}
		}
	}

	if (DestinationCheckpointClass)
	{
		TArray<AActor*> FoundDestinationCheckpoints;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DestinationCheckpointClass, FoundDestinationCheckpoints);

		for (AActor* FoundDestinationCheckpointActor : FoundDestinationCheckpoints)
		{
			if (const ADestinationCheckpoint* DestinationCheckpoint = Cast<ADestinationCheckpoint>(FoundDestinationCheckpointActor))
			{
				FDestination NewDestination = FDestination();
			
				NewDestination.Id = DestinationCheckpoint->Id;
				NewDestination.Location = DestinationCheckpoint->GetActorLocation();
				NewDestination.Name = DestinationCheckpoint->Name;
			
				GameInstance->Destinations.Add(NewDestination);
			}
		}
	}
}
