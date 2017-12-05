// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnBall.generated.h"

UCLASS()
class UE4PG2_API AMyPawnBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	
	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartJumping();
	void StopJumping();
	void StartBoosting();
	void StopBoosting();

	// Input variables
	FVector CurrentVelocity;
	bool bJumping;
	bool bBoosting;
	float JumpRate = 2.0f;
	float BoostAmt = 4.0f;
};
