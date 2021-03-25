// Copyright Leonardo Porto 2020


#include "OpenSkeletonDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenSkeletonDoor::UOpenSkeletonDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenSkeletonDoor::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> Meshes;
	GetOwner()->GetComponents<UStaticMeshComponent>(Meshes);

	for (UStaticMeshComponent* Mesh : Meshes)
	{
		if (Mesh->GetName().Equals(TEXT("SM_DoorWay_Large_Door_Left")))
		{
			LeftDoorMesh = Mesh;
		}
		else if (Mesh->GetName().Equals(TEXT("SM_DoorWay_Large_Door_Right")))
		{
			RightDoorMesh = Mesh;
		}
	}

	InitialYawLeftDoor = LeftDoorMesh->GetComponentRotation().Yaw;
	CurrentYawLeftDoor = InitialYawLeftDoor;
	OpenAngleLeftDoor += InitialYawLeftDoor;

	InitialYawRightDoor = RightDoorMesh->GetComponentRotation().Yaw;
	CurrentYawRightDoor = InitialYawRightDoor;
	OpenAngleRightDoor += InitialYawRightDoor;
}


// Called every frame
void UOpenSkeletonDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor(DeltaTime);
	}
}

void UOpenSkeletonDoor::OpenDoor(float DeltaTime)
{
	CurrentYawLeftDoor = FMath::FInterpTo(CurrentYawLeftDoor, OpenAngleLeftDoor, DeltaTime, DoorOpenSpeed);
	CurrentYawRightDoor = FMath::FInterpTo(CurrentYawRightDoor, OpenAngleRightDoor, DeltaTime, DoorOpenSpeed);
	
	FRotator LeftDoorRotation = LeftDoorMesh->GetComponentRotation();
	LeftDoorRotation.Yaw = CurrentYawLeftDoor;
	LeftDoorMesh->SetWorldRotation(LeftDoorRotation);

	FRotator RightDoorRotation = RightDoorMesh->GetComponentRotation();
	RightDoorRotation.Yaw = CurrentYawRightDoor;
	RightDoorMesh->SetWorldRotation(RightDoorRotation);
}

