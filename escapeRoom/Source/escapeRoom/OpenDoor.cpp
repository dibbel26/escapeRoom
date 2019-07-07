// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}

void UOpenDoor::OpenDoor()
{
	//get current rotator, modify, set
	FRotator CurrentRotator = GetOwner()->GetActorRotation();

	CurrentRotator.Add(0.f, OpenAngle, 0.f);

	GetOwner()->SetActorRotation(CurrentRotator);
	
}

void UOpenDoor::CloseDoor()
{
	FRotator CurrentRotator = GetOwner()->GetActorRotation();

	CurrentRotator.Add(0.f, -OpenAngle, 0.f);

	GetOwner()->SetActorRotation(CurrentRotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if ((!DoorOpen) && (PressurePlate->IsOverlappingActor(ActorThatOpens))) {
		OpenDoor();
		DoorOpen = true;
	}
	else if (DoorOpen && !(PressurePlate->IsOverlappingActor(ActorThatOpens))) {
		CloseDoor();
		DoorOpen = false;
	}
	// If the ActorThatOpens is in the volume
}

