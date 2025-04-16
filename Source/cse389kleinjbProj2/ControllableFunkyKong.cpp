// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableFunkyKong.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AControllableFunkyKong::AControllableFunkyKong()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AControllableFunkyKong::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControllableFunkyKong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AControllableFunkyKong::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PC = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	PEI->BindAction(IAMove, ETriggerEvent::Triggered, this, &AControllableFunkyKong::Move);
	PEI->BindAction(IALook, ETriggerEvent::Triggered, this, &AControllableFunkyKong::Look);
	PEI->BindAction(IAJump, ETriggerEvent::Triggered, this, &AControllableFunkyKong::Jump);
}

void AControllableFunkyKong::Move(const FInputActionValue& value)
{
	if (Controller != nullptr) {
		const FVector2D move = value.Get<FVector2D>();
		const FRotator moverot(0, Controller->GetControlRotation().Yaw, 0);
		if (move.Y != 0.f)
			AddMovementInput(moverot.RotateVector(FVector::ForwardVector), move.Y);
		if (move.X != 0.f)
			AddMovementInput(moverot.RotateVector(FVector::RightVector), move.X);
	}
}

void AControllableFunkyKong::Look(const FInputActionValue& value)
{
	if (Controller != nullptr) {
		const FVector2d look = value.Get<FVector2D>();
		if (look.X != 0.f)
			AddControllerYawInput(look.X);
		if (look.Y != 0.f)
			AddControllerPitchInput(-look.Y);
	}
}

void AControllableFunkyKong::Jump(const FInputActionValue& value)
{
	ACharacter* Character = Cast<ACharacter>(this);
	if (Character && !Character->GetCharacterMovement()->IsFalling())
		Character->Jump();
}

