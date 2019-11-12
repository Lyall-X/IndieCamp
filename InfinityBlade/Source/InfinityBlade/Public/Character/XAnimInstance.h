// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "XAnimInstance.generated.h"

/**
 * 英雄角色的动画实例
 */
UCLASS()
class INFINITYBLADE_API UXAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
		/** 人物的移动速度 */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;

		/** 是否处于攻击状态 */
		bool bIsAttacking;
		/** 是否处于播放状态 */
		bool bIsPlaying;
		/** 是否进入第二次连击 */
		bool bIsEnableSecondAttack;
		/** 是否进入第三次连击 */
		bool bIsEnableThreeAttack;
		/** 是否进入第四次连击 */
		bool bIsEnableFourAttack;
		/** 是否进入第五次连击 */
		bool bIsEnableFiveAttack;

public:
	/** 更新人物移动速度 */
	UFUNCTION(BlueprintCallable)
		void UpdateSpeed();

public:
	/** 开始播放蒙太奇 */
	UFUNCTION()
		void AnimNotify_PlayStart(UAnimNotify* Notify);
	/** 结束播放蒙太奇 */
	UFUNCTION()
		void AnimNotify_PlayEnd(UAnimNotify* Notify);

	/** 重置连击状态 */
	UFUNCTION()
		void AnimNotify_ResetSerialAttack(UAnimNotify* Notify);
	/** 进入第二次连击 */
	UFUNCTION()
		void AnimNotify_SecondAttackInput(UAnimNotify* Notify);
	/** 进入第三次连击 */
	UFUNCTION()
		void AnimNotify_ThreeAttackInput(UAnimNotify* Notify);
	/** 进入第四次连击 */
	UFUNCTION()
		void AnimNotify_FourAttackInput(UAnimNotify* Notify);
	/** 进入第五次连击 */
	UFUNCTION()
		void AnimNotify_FiveAttackInput(UAnimNotify* Notify);
};
