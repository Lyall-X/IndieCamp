// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "AI/MonsterController.h"
#include "AI/AICharacter.h"
#include "AI/AIAnimInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/** 重写执行任务节点 */
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/** 获取Controller */
	AMonsterController* Controller = Cast<AMonsterController>(OwnerComp.GetAIOwner());
	/** 获取AI */
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());
	/** 获取动画实例 */
	UAIAnimInstance* AIAnimInstance = Cast<UAIAnimInstance>(Monster->GetMesh()->GetAnimInstance());
	/** 判断当前是否正在播放动画蒙太奇 */
	if (!AIAnimInstance->bIsPlaying)
	{
		/** 朝向玩家 */
		Controller->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		/** 获取随机数 */
		uint8 RandomNum = FMath::FloorToInt(FMath::RandRange(0.f, Monster->AttackMontages.Num()*1.f));
		/** 随机播放动画蒙太奇 */
		AIAnimInstance->Montage_Play(Monster->AttackMontages[RandomNum], 1.f);
	}

	return EBTNodeResult::Succeeded;
}
