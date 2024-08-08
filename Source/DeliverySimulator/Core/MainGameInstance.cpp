// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UMainGameInstance::Init()
{
	Super::Init();

	OrdersSubsystem = NewObject<UOrdersSubsystem>(UOrdersSubsystem::StaticClass());
	OrdersSubsystem->InitializeSubsystem(ProductsDataTable, GetTimerManager());

	StatsSubsystem = NewObject<UStatsSubsystem>(UStatsSubsystem::StaticClass());
	StatsSubsystem->InitializeSubsystem();
}

 