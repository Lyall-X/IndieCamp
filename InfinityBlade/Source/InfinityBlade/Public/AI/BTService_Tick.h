// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Tick.generated.h"

/**
 * ���ڰ���Զ���Service
 */
UCLASS()
class INFINITYBLADE_API UBTService_Tick : public UBTService
{
	GENERATED_BODY()

public:
	/** ��д�����ڵ� */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};