// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"
// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
    
	OriginalRotation = GetOwner()->GetActorRotation();
	OriginalLocation = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    RotateDoor(DeltaTime);
	MoveDoor(DeltaTime);
	
}

void UMover::RotateDoor(float DeltaTime) {
	if (ShouldRotate) {
    	FRotator CurrRotation = GetOwner()->GetActorRotation();
		FRotator TargetRotation = OriginalRotation + RotateOffset;
		float Speed = (TargetRotation.Yaw - OriginalRotation.Yaw) / MoveTime;
    	FRotator NewRotation = FMath::RInterpConstantTo(CurrRotation, TargetRotation, DeltaTime, Speed);
		GetOwner()->SetActorRotation(NewRotation);
	}
}

void UMover::MoveDoor(float DeltaTime) {
	FVector TargetLocation = OriginalLocation;
	
	if (ShouldMove) {
    	TargetLocation = OriginalLocation + MoveOffset;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
}



void UMover::SetShouldRotate(bool NewValue) {
	ShouldRotate = NewValue;
}

void UMover::SetShouldMove(bool NewValue) {
	ShouldMove = NewValue;
}

