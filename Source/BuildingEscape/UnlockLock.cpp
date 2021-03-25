// Copyright Leonardo Porto 2020


#include "UnlockLock.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectIterator.h"
#include "OpenCellDoor.h"

// Sets default values for this component's properties
UUnlockLock::UUnlockLock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UUnlockLock::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UUnlockLock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OUT OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		if (Actor == KeyActor)
		{
			SwitchMesh();
			UnlockDoor();
		}
	}
}

void UUnlockLock::SwitchMesh()
{
	UStaticMeshComponent* StaticMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	UStaticMesh* UnlockedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Props/SM_Lock_Open.SM_Lock_Open'")));
	StaticMesh->SetStaticMesh(UnlockedMesh);
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
}

void UUnlockLock::UnlockDoor()
{
	for(TObjectIterator<UOpenCellDoor> Itr; Itr; ++Itr)
	{
		Itr->UnlockDoor();
	}
}

