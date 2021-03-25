// Copyright Leonardo Porto 2020


#include "OpenGargoyleDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenGargoyleDoor::UOpenGargoyleDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenGargoyleDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialZ = GetOwner()->GetActorLocation().Z;
	CurrentZ = InitialZ;

	FindPressurePlate();
	FindActorThatOpens();
}


// Called every frame
void UOpenGargoyleDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && !PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor(DeltaTime);
	}
}

void UOpenGargoyleDoor::OpenDoor(float DeltaTime)
{
	CurrentZ = FMath::FInterpTo(CurrentZ, OpenPosition, DeltaTime, DoorOpenSpeed);
	FVector DoorLocation = GetOwner()->GetActorLocation();
	DoorLocation.Z = CurrentZ;
	GetOwner()->SetActorLocation(DoorLocation);
}

void UOpenGargoyleDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenGargoyleDoor component but no PressurePlate set."), *GetOwner()->GetName());
	}
}

void UOpenGargoyleDoor::FindActorThatOpens()
{
	if (!ActorThatOpensDoor)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenGargoyleDoor component but no Actor set."), *GetOwner()->GetName());
	}
}

