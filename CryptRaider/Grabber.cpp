// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent()) {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	// FVector Start = GetComponentLocation();
    // FVector End = Start + GetForwardVector() * MaxGrabDistance;
    // DrawDebugLine(GetWorld(), Start, End, FColor::Red);
}

void UGrabber::Grab() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}

	FHitResult HitResult;
    bool HasHit = GetGrabbableInReach(HitResult);
    
	if (HasHit) {
		// AActor* HitActor = HitResult.GetActor();
		// FString ActorHitName = HitActor->GetActorNameOrLabel();
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Purple, false, 5);
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		AActor* HitActor = HitResult.GetActor();
		if (HitActor->ActorHasTag("Coffin")) {
			return;
		}

		HitComponent->WakeAllRigidBodies();
		HitComponent->SetSimulatePhysics(true);
		
		

		

		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		HitActor->Tags.Add("Grabbed");
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	} 
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const {
  FVector Start = GetComponentLocation();
  FVector End = Start + GetForwardVector() * MaxGrabDistance;
  //DrawDebugLine(GetWorld(), Start, End, FColor::Red);
  //DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);
  FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRaduis);
  return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
  
}

void UGrabber::Release() {
	//UE_LOG(LogTemp, Display, TEXT("Released Grabber"));
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent()) {
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const {
	UPhysicsHandleComponent* Result;
	Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Grabber requires PhysicsHandle"));
	}
	return Result;
}

