// Copyright Leonardo Porto 2020

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	// if (FMath::IsNearlyEqual(InitialYaw, 90.f, 0.1f)) {
	// 	OpenAngle = InitialYaw - 90.f;	
	// } else {
	// 	OpenAngle = InitialYaw + 90.f;
	// }
	OpenAngle += InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassThreshold) 
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSoundPlayed = false;
	if (!DoorSound) {return;}
	if (!OpenDoorSoundPlayed) 
	{
		DoorSound->Play();
		OpenDoorSoundPlayed = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSoundPlayed = false;
	if (!DoorSound) {return;}
	if (!CloseDoorSoundPlayed)
	{
		DoorSound->Play();
		CloseDoorSoundPlayed = true;
	}
}

float UOpenDoor::TotalMassOfActors() const 
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component but no PressurePlate set."), *GetOwner()->GetName());
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent() 
{
	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorSound) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s does not have an Audio Component"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component but no PressurePlate set."), *GetOwner()->GetName());
	}
}

