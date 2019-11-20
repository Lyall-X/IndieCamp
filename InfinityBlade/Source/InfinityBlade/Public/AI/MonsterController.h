// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Weapon/Weapon.h"
#include "MonsterController.generated.h"

/**
 * AI控制器
 */
UCLASS()
class INFINITYBLADE_API AMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	/** 行为树控件 */
	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent;
	/** 黑板控件 */
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent;
	/** 武器对象 */
	UPROPERTY()
		AWeapon* AIWeapon;

public:
	/** 构造方法 */
	AMonsterController();
	/** 重写控制的方法 */
	virtual void OnPossess(APawn* InPawn) override;
};
