// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent) //this is allowing us to make this function accessible inside the blueprints
	void StartGame(); //dont need to give it a body inside c++ but we can call it from c++ so that is what we are going to do
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
private:
	class ATank* tank;
	class ATankPlayerController* playerController;
	float StartDelay = 3.f;
	void HandleGameStart();
	int32 TargetTowers = 0;
	int32 GetTowerCount();
};
