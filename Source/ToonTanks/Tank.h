// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank(); //name should be the same as the one shown above ATank
	//this function allows us to handle input from a keyboard or mouse
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	//issue was that i did not forward declare them
	UPROPERTY(VisibleAnywhere,Category= "Camera");
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, Category= "Camera");
	class UCameraComponent* camera;
	UPROPERTY(EditAnywhere, Category="Movement");
	float speed;
	UPROPERTY(EditAnywhere,Category = "Movement");
	float rotationSpeed;
	void Move(float value);
	void Turn(float value);
	APlayerController* controller;

};
