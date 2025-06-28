// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:
	class ATank* tank; //name of the pointer is the same as the name of the class assigned by unreal not the file name
	UPROPERTY(EditAnywhere,Category="Tower")
	float fireRange = 300.f;
	FTimerHandle FireRateTimerHandle;
	float FireRate =2.f;
	void CheckFireCondition();

};
