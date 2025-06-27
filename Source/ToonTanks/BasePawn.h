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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite) //exposes this variable to the event graph
	float VisibleDefaultOnly = 2.4;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) //this makes it only read only in the events graph
	float EditDefaultsOnly = 2.4; //only editable in the blueprint class

	

protected:
	void RotateTurret(FVector lookAtTarget);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"));
	class UCapsuleComponent* CapsuleComp; //reason we wrote class in front of it was that 
	//we did not want to include the whole header file because that will in result lead to a 
	//larger file

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh; //added by default in all actors so we dont need to forward declare it

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Super Variable", meta = (AllowPrivateAccess = "true")); //what this does is allows the private variable to be accessed in the event graph as well
	int32 VisibleAnywhere = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Super Variable", meta = (AllowPrivateAccess = "true"));
	int32 EditAnywhere = 2;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override; 
	
	// Called to bind functionality to input
	//this function allows us to handle input from a keyboard or mouse
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//removing this because our tower (enemy) does not need to have this so removing this from here and adding
	//it to tank.cpp
};
