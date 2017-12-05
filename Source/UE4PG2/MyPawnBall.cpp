// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnBall.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMyPawnBall::AMyPawnBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyPawnBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawnBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation;

	// Handle movement based on our "MoveX" and "MoveY" axes
	if (!CurrentVelocity.IsZero()) {

		float CurrentBoost = bBoosting * BoostAmt + 1.0f;

		NewLocation = GetActorLocation() + (CurrentVelocity * CurrentBoost * DeltaTime);
		SetActorLocation(NewLocation);
	}

	// Handle jumping based on our "Jump" action
	FVector CurrentPosition = GetActorLocation();

	if (bJumping) {
		CurrentPosition.Z += JumpRate;
	}
	else {
		CurrentPosition.Z -= JumpRate;
	}

	// Constrain movement in Z
	CurrentPosition.Z = FMath::Clamp(CurrentPosition.Z, 20.0f, 250.0f);
	SetActorLocation(CurrentPosition);
}

// Called to bind functionality to input
void AMyPawnBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Jump" key is pressed or released
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPawnBall::StartJumping);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPawnBall::StopJumping);

	// Respond when our "Boost" key is pressed or released
	InputComponent->BindAction("Boost", IE_Pressed, this, &AMyPawnBall::StartBoosting);
	InputComponent->BindAction("Boost", IE_Released, this, &AMyPawnBall::StopBoosting);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY"
	InputComponent->BindAxis("MoveX", this, &AMyPawnBall::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawnBall::Move_YAxis);
}

void AMyPawnBall::Move_XAxis(float AxisValue){
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawnBall::Move_YAxis(float AxisValue){
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawnBall::StartJumping()
{
	bJumping = true;
}

void AMyPawnBall::StopJumping()
{
	bJumping = false;
}

void AMyPawnBall::StartBoosting()
{
	bBoosting = true;
}

void AMyPawnBall::StopBoosting()
{
	bBoosting = false;
}

