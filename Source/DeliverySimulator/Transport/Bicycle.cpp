// Fill out your copyright notice in the Description page of Project Settings.


#include "Bicycle.h"
#include "ChaosVehicleMovementComponent.h"
#include "../Character/ThirdPersonCharacter.h"
#include "EventManager.h"

FBikePoints::FBikePoints(const FVector& InSeat, const FVector& InLeftHand, const FVector& InRightHand, 
						 const FVector& InLeftPedal, const FVector& InRightPedal)
	: Seat(InSeat), LeftHand(InLeftHand), RightHand(InRightHand), LeftPedal(InLeftPedal), RightPedal(InRightPedal)
{
}


ABicycle::ABicycle()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);

	GetIntoBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GetIntoBox"));
	GetIntoBoxCollision->SetupAttachment(RootComponent);
	
	GetMesh()->SetSimulatePhysics(true);
}

void ABicycle::BeginPlay()
{
	Super::BeginPlay();

	GetIntoBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABicycle::OnBoxOverlapBegin);
	GetIntoBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABicycle::OnBoxOverlapEnd);
}

void ABicycle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Camera
	PlayerInputComponent->BindAxis("LookRight", this, &ABicycle::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABicycle::LookUp);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABicycle::MoveForward);
	PlayerInputComponent->BindAxis("TurnLeft", this, &ABicycle::TurnLeft);
	PlayerInputComponent->BindAxis("MoveBack", this, &ABicycle::MoveBack);

	// Break
	PlayerInputComponent->BindAction("HandBrake", EInputEvent::IE_Pressed, this, &ABicycle::StartHandBrake);
	PlayerInputComponent->BindAction("HandBrake", EInputEvent::IE_Released, this, &ABicycle::StopHandBrake);

	// Exit
	PlayerInputComponent->BindAction("GetInside", IE_Pressed, this, &ABicycle::GetOutOfBicycle);
}

void ABicycle::LookRight(const float Scale)
{
	AddControllerYawInput(Scale);
}

void ABicycle::LookUp(const float Scale)
{
	AddControllerPitchInput(Scale);
}

void ABicycle::MoveForward(const float Scale)
{
	GetVehicleMovementComponent()->SetThrottleInput(Scale);
}

void ABicycle::TurnLeft(const float Scale)
{
	GetVehicleMovementComponent()->SetSteeringInput(Scale);
}

void ABicycle::MoveBack(const float Scale)
{
	GetVehicleMovementComponent()->SetBrakeInput(-Scale);
}

void ABicycle::StartHandBrake()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}
void ABicycle::StopHandBrake()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ABicycle::GetOutOfBicycle()
{
	if (!GetOutOfBicycleMontage) return;
	
	StartHandBrake();
	const bool bRightBody = SideRayCast(GetMesh()->GetRightVector());
	const bool bLeftBody = SideRayCast(-GetMesh()->GetRightVector());

	if (!bRightBody || !bLeftBody)
	{
		bMirrorAnimations = bRightBody;

		UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
		if (!AnimInstance->Montage_IsPlaying(GetOutOfBicycleMontage))
		{
			int32 const SectionIndex = GetOutOfBicycleMontage->GetSectionIndex("Default");
			int32 const SectionLength = GetOutOfBicycleMontage->GetSectionLength(SectionIndex);


			const FVector PossessLocation = bRightBody ?
				GetMesh()->GetSocketLocation("get_from_right_socket") :
				GetMesh()->GetSocketLocation("get_from_left_socket");

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AThirdPersonCharacter* Character = GetWorld()->SpawnActor<AThirdPersonCharacter>(CharacterClass, PossessLocation, GetActorRotation(), SpawnParams);
			Character->GetMesh()->SetVisibility(false);

			APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->SetViewTargetWithBlend(Character, 2.f);


			AnimInstance->Montage_Play(GetOutOfBicycleMontage);
			GetWorldTimerManager().SetTimer(GetOutOfBicycleHandle, [this, Character]()
			{
				PossessCharacter(Character);
			}, SectionLength, false);
		}
	}
}

float ABicycle::GetAcceleration() const
{
	if (InputComponent)
		return InputComponent->GetAxisValue("MoveForward") + (InputComponent->GetAxisValue("MoveBack"));
	return 0;
}

FBikePoints ABicycle::GetBikePoints() const
{
	// Get the mesh component
	const USkeletalMeshComponent* MeshComponent = GetMesh();

	// Ensure MeshComponent is valid
	if (!MeshComponent)
	{
		return FBikePoints();
	}

	// Get the world locations of the sockets
	FTransform SeatLocation = MeshComponent->GetSocketTransform("seat");
	FTransform LeftHandLocation = MeshComponent->GetSocketTransform("left_hand");
	FTransform RightHandLocation = MeshComponent->GetSocketTransform("right_hand");
	FTransform LeftPedalLocation = MeshComponent->GetSocketTransform("penal_left");
	FTransform RightPedalLocation = MeshComponent->GetSocketTransform("pedal_right");

	FTransform CharacterWorldTransform = CharacterMesh->GetComponentTransform();

	// Create FTransforms using the local locations
	FTransform LocalSeatTransform = UKismetMathLibrary::MakeRelativeTransform(SeatLocation, CharacterWorldTransform);
	FTransform LocalLeftHandTransform = UKismetMathLibrary::MakeRelativeTransform(LeftHandLocation, CharacterWorldTransform);
	FTransform LocalRightHandTransform = UKismetMathLibrary::MakeRelativeTransform(RightHandLocation, CharacterWorldTransform);
	FTransform LocalLeftPedalTransform = UKismetMathLibrary::MakeRelativeTransform(LeftPedalLocation, CharacterWorldTransform);
	FTransform LocalRightPedalTransform = UKismetMathLibrary::MakeRelativeTransform(RightPedalLocation, CharacterWorldTransform);
	
	// Create and return FBikePoints with local transforms
	FBikePoints Points = FBikePoints(
		LocalSeatTransform.GetTranslation(),
		LocalLeftHandTransform.GetTranslation(),
		LocalRightHandTransform.GetTranslation(),
		LocalLeftPedalTransform.GetTranslation(),
		LocalRightPedalTransform.GetTranslation()
	);

	return Points;
}

void ABicycle::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AThirdPersonCharacter* Character = Cast<AThirdPersonCharacter>(OtherActor))
	{
		Character->HandleEnterBicycleCollision(this);

	}
}

void ABicycle::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AThirdPersonCharacter* Character = Cast<AThirdPersonCharacter>(OtherActor))
	{
		Character->HandleExitBicycleCollision(this);
	}
}

bool ABicycle::SideRayCast(const FVector& Direction) const
{
	FVector RayStart = GetMesh()->GetComponentLocation();
	FVector RayEnd = RayStart + (Direction * 150.f);
	
	constexpr float VerticalOffset = 50.f;

	RayStart.Z += VerticalOffset;
	RayEnd.Z += VerticalOffset;

	FHitResult hit;
	if (GetWorld() &&
		GetWorld()->LineTraceSingleByChannel(hit, RayStart, RayEnd, ECC_PhysicsBody))
	{
		if (hit.GetActor())
		{
			return true;
		}
	}
	
	//DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Red, false, 5.f, 0, 5);

	return false;
}

void ABicycle::PossessCharacter(AThirdPersonCharacter* Character)
{
	CharacterMesh->SetVisibility(false);
	Character->GetMesh()->SetVisibility(true);
	
	if (Character)
	{
		GetController()->Possess(Character);
	}
}
