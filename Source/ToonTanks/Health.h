// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) //this meta blueprintspawnable is what will allow us to access this in
//blueprint
class TOONTANKS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f; 
	float Health = 0.f;
	class AActor* Owner;
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);
	//so the first parameter is the actor that was damaged
	//second one is the amount of damage that was done to that actor
	//third is the damagetype in unreal we have explosive damage,poison damage and we can make our custom damage as well
	//fourth parameter is the controller that caused that damage in one of the case our player controller
	//fifth parameter is the actor that caused the damage
	class AToonTanksGameMode* gameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
