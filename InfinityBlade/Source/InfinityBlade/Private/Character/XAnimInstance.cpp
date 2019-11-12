// Fill out your copyright notice in the Description page of Project Settings.


#include "XAnimInstance.h"


/** 更新人物移动速度 */
void UXAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}

/** 开始播放蒙太奇 */
void UXAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/** 结束播放蒙太奇 */
void UXAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

/** 重置连击状态 */
void UXAnimInstance::AnimNotify_ResetSerialAttack(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = false;
	bIsEnableThreeAttack = false;
	bIsEnableFourAttack = false;
	bIsEnableFiveAttack = false;
}

/** 进入第二次连击 */
void UXAnimInstance::AnimNotify_SecondAttackInput(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = true;
}

/** 进入第三次连击 */
void UXAnimInstance::AnimNotify_ThreeAttackInput(UAnimNotify* Notify)
{
	bIsEnableThreeAttack = true;
}

/** 进入第四次连击 */
void UXAnimInstance::AnimNotify_FourAttackInput(UAnimNotify* Notify)
{
	bIsEnableFourAttack = true;
}

/** 进入第五次连击 */
void UXAnimInstance::AnimNotify_FiveAttackInput(UAnimNotify* Notify)
{
	bIsEnableFiveAttack = true;
}
