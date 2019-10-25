// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_DistanceTo.generated.h"

/**
 * 判断距离的装饰器
 */
UCLASS()
class INFINITYBLADE_API UBTDecorator_DistanceTo : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	/** 判断的距离 */
	UPROPERTY(EditAnywhere, Category = "Prop")
		float Distance;
	/** 重写判断的方法 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	
	
};
