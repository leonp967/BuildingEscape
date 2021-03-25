// Copyright Leonardo Porto 2020


#include "OpenCellDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenCellDoor::UOpenCellDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenCellDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	FindAudioComponent();
}


// Called every frame
void UOpenCellDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorUnlocked)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenCellDoor::OpenDoor(float DeltaTime)
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

void UOpenCellDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSoundPlayed = false;
	DoorUnlocked = false;
	if (!DoorSound) {return;}
	if (!CloseDoorSoundPlayed)
	{
		DoorSound->Play();
		CloseDoorSoundPlayed = true;
	}
}

void UOpenCellDoor::FindAudioComponent() 
{
	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorSound) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s does not have an Audio Component"), *GetOwner()->GetName());
	}
}

void UOpenCellDoor::UnlockDoor()
{
	DoorUnlocked = true;
}
