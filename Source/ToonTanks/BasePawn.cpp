// Fill out your copyright notice in the Description page of Project Settings.



#include "BasePawn.h"
#include "Components/CapsuleComponent.h" //if had not included this file it would have given the error that undefined UCapsuleComponent 
// Sets default values
ABasePawn::ABasePawn() //this is the class constructor
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; //we are basically changing the address of rootcomponent so it points to the capsulecomponent

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp); //attaches this to the capsulecomp
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT ("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(TurretMesh);


}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

