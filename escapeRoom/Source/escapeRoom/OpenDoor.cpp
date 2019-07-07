// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UOpenDoor::IsDoorOpen() const { return DoorOpen; }
FRotator UOpenDoor::GetRotatorOnBegin() const { return RotatorOnBegin; };

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	RotatorOnBegin = GetOwner()->GetActorRotation();
}


void UOpenDoor::OpenDoor()
{
	// get RotatorOnBegin, modify, set

	GetOwner()->SetActorRotation(GetRotatorOnBegin().Add(0.f, OpenAngle, 0.f));
	DoorOpen = true;
}

void UOpenDoor::CloseDoor()
{
	// reset FRotator
	GetOwner()->SetActorRotation(GetRotatorOnBegin());
	DoorOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// if door is open, the PressuraPlate is deactivated and the DoorCloseDelay has passed close the door.
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}else if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}

}
