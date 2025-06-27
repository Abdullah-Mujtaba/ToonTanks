// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h" //needed for the springArm look at documentation for every header usually
//different components will have different header files also since these were not already inside our base pawn
//class we had to incude them manually
#include "Camera/CameraComponent.h" //needed for the camera
#include "Kismet/GameplayStatics.h"
ATank::ATank()    
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    springArm->SetupAttachment(RootComponent);
    camera->SetupAttachment(springArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
}

void ATank::Move(float value) //called every second because it is being passed as a parameter in SetupPLayerInputComponent
{
    FVector DeltaLocation(0.f);
    //another way to initialise a function with zero values is 
    //FVector DeltaLocation = FVector::ZeroVector;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X = value*DeltaTime*speed;
    AddActorLocalOffset(DeltaLocation); //forgot to add this when testing first and that is why it was not moving
    //UE_LOG(LogTemp,Warning,TEXT("Value: %f"), value);
}