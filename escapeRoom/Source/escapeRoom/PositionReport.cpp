// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();

	//FVector ObjectLocation = GetOwner()->GetActorLocation();
	FVector ObjectLocation2= GetOwner()->GetTransform().GetLocation();

	//FString ObjectPos = ObjectLocation.ToCompactString();
	FString ObjectPos = ObjectLocation2.ToCompactString();


	
	UE_LOG(LogTemp, Warning, TEXT("%s ist at %s"), *ObjectName, *ObjectPos);//Overloaded Operator, returns TChar[]* of FString
		
	//GetOwner()->SetActorLocation(ObjectLocation + FVector(0, 0, 100)); hard-coded movement of objects
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0, 0, 1)); That was fun :D
	// ...
}

