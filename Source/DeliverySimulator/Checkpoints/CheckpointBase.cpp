// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointBase.h"

// Sets default values
ACheckpointBase::ACheckpointBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	MainMeshComponent->SetupAttachment(CollisionComponent);
}

// Called when the game starts or when spawned
void ACheckpointBase::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointBase::OnCollisionEnter);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACheckpointBase::OnCollisionExit);
	}
}

// Called every frame
void ACheckpointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

