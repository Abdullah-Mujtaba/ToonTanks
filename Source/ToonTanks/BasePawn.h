// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //protects the file from being included multiple times

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY();
	class UCapsuleComponent* CapsuleComp; //reason we wrote class in front of it was that 
	//we did not want to include the whole header file because that will in result lead to a 
	//larger file

	UPROPERTY()
	UStaticMeshComponent* BaseMesh; //added by default in all actors so we dont need to forward declare it

	UPROPERTY()
	UStaticMeshComponent* TurretMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//this function allows us to handle input from a keyboard or mouse
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
