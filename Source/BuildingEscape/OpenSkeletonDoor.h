// Copyright Leonardo Porto 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenSkeletonDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenSkeletonDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenSkeletonDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void FindPressurePlate();
	void FindActorThatOpens();
		
private:
	float CurrentYawRightDoor;
	float CurrentYawLeftDoor;
	float InitialYawRightDoor;
	float InitialYawLeftDoor;
	UStaticMeshComponent* LeftDoorMesh = nullptr;
	UStaticMeshComponent* RightDoorMesh = nullptr;

	UPROPERTY(EditAnywhere)
	float OpenAngleRightDoor = 0.f;

	UPROPERTY(EditAnywhere)
	float OpenAngleLeftDoor = -180.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.5f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensDoor;
};
