// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAnimInstance.h"
#include "AI/MonsterController.h"

/** 更新人物移动速度 */
void UAIAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}

/** 开始播放蒙太奇 */
void UAIAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/** 结束播放蒙太奇 */
void UAIAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

/** 死亡动画通知 */
void UAIAnimInstance::AnimNotify_Death(UAnimNotify* Notify)
{
	AMonsterController* Controller = Cast<AMonsterController>(TryGetPawnOwner()->GetController());
	Controller->AIWeapon->Destroy();
	TryGetPawnOwner()->Destroy();
}