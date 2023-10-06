// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	void SetShouldRotate(bool NewValue);

	void SetShouldMove(bool NewValue);

	UFUNCTION(BlueprintCallable)
	bool GetShouldRotate() {return ShouldRotate;}

	UFUNCTION(BlueprintCallable)
	bool GetShouldMove() {return ShouldMove;}

private:

	UPROPERTY(EditAnywhere)
    FRotator RotateOffset;

	UPROPERTY(EditAnywhere)
    FVector MoveOffset;

	UPROPERTY(EditAnywhere)
    float MoveTime = 4;	

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;

	UPROPERTY(EditAnywhere)
	bool ShouldRotate = false;

	// UPROPERTY(EditAnywhere)
	// class USoundBase* MovingSound;
	
	FRotator OriginalRotation;
	FVector OriginalLocation;	

	void RotateDoor(float DeltaTime);

	void MoveDoor(float DeltaTime);

	// void PlayMovingSound(bool bShouldPlay);
};
