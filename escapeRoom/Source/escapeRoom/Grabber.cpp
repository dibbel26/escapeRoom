// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"))

		///Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s is missing a UPhysicsHandleComponent"), *(GetOwner()->GetName()))
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has an Input Component"), *(GetOwner()->GetName()))
			// Bind the input axis
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
			InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s misses an Input Component"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"))
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPoint,
		OUT PlayerViewPointRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("%s -- %s"), *(PlayerViewPoint.ToString()), *(PlayerViewPointRotation.ToString()))


	FVector	LineTraceEnd = PlayerViewPoint + PlayerViewPointRotation.Vector() * Reach;
	
	DrawDebugLine(
		GetWorld(),
		PlayerViewPoint,
		LineTraceEnd,
		FColor::FromHex("#00ff00"),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	

	/// Line-trace (Ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPoint,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// See what we hit
	if (Hit.GetActor() != NULL) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(Hit.GetActor()->GetName()))
	}
	
	
}

