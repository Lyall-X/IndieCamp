// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_DistanceTo.h"
#include "AI/MonsterController.h"
#include "AI/AICharacter.h"

/** 重写判断的方法 */
bool UBTDecorator_DistanceTo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	/** 获取Controller */
	AMonsterController* Controller = Cast<AMonsterController>(OwnerComp.GetAIOwner());
	/** 获取AI */
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());
	/** 获取黑板控件 */
	UBlackboardComponent* Blackboard = Controller->BlackboardComponent;

	/** 获取目标位置 */
	FVector TargetLocation = Blackboard->GetValueAsVector(TEXT("TargetLocation"));
	/** 获取两者距离 */
	float Distance = FVector::Distance(Controller->GetPawn()->GetActorLocation(), TargetLocation);
	/** 判断 */
	if (Distance <= this->Distance)
	{
		return true;
	}

	return false;
}
