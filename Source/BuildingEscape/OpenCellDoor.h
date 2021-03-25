// Copyright Leonardo Porto 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "OpenCellDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenCellDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenCellDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void UnlockDoor();

private:
	float CurrentYaw;
	float InitialYaw;
	float DoorLastOpened = 0.f;
	bool DoorUnlocked = false;
	bool CloseDoorSoundPlayed = true;
	bool OpenDoorSoundPlayed = false;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 3.f;

	UPROPERTY()
	UAudioComponent* DoorSound = nullptr;
};
