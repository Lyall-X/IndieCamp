// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 攻击任务节点
 */
UCLASS()
class INFINITYBLADE_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	/** 重写执行任务节点 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
