// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("TriggerComponent Alive"));

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

    AActor* Actor = GetKeyActor();
    if (Actor) {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component) {
            Component->SetSimulatePhysics(false);
        }

        Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        
        if (Mover && Mover->GetOwner()->ActorHasTag("RotateDoor")) {
            Mover->SetShouldRotate(true);
        } else if (Mover && Mover->GetOwner()->ActorHasTag("MoveDoor")) {
            Mover->SetShouldMove(true);
        }
        if (Locker) {
            Locker->SetIsLocked(false);
        }          
    } else {
        if (Mover && Mover->GetOwner()->ActorHasTag("RotateDoor")) {
            Mover->SetShouldRotate(false);
        } else if (Mover && Mover->GetOwner()->ActorHasTag("MoveDoor")) {
            Mover->SetShouldMove(false);
        }

        if (Locker) {
            Locker->SetIsLocked(true);
        }  
    }
}

void UTriggerComponent::SetMover(UMover* NewMover) {
    Mover = NewMover;
}

void UTriggerComponent::SetLocker(ULocker* NewLocker) {
    Locker = NewLocker;
}

AActor* UTriggerComponent::GetKeyActor() const {
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for (AActor* Actor : Actors) {
        if(Actor->ActorHasTag(KeyName) && !Actor->ActorHasTag("Grabbed")) {
            return Actor;
        }
    }
    return nullptr;
}



