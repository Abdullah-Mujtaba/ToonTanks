// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// class SoundBase this is another way to forward declare it so we do not have to forward declare our first instance

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly,Category = "Combat");
	UStaticMeshComponent* ProjectileMesh; //added by default in all actors so we dont need to forward declare it
	UPROPERTY(VisibleAnywhere, Category = "Combat");
	class UProjectileMovementComponent* ProjectileMovement;
	UFUNCTION()//we are doing this so we can bind it to a delegate, UFunction is the same thing as UProperty but for functions only
	//it was an additional semicolon that caused the issue with the udefined variable for UFUNCTION
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles; 
	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* SmokeTrail;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere,Category="Combat")
	USoundBase* HitSound; // no need to forward declare it again because it was done once
	UPROPERTY(EditAnywhere, Category="Combat")
	class TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
	//“Create a variable that will store the class (not an instance) of any camera-shake asset derived from UCamerShakeBase. 
	//Designers can pick a shake blueprint in the Details panel, and at runtime we can play that shake.”
};
