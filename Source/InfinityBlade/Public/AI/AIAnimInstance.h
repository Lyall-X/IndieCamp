// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.generated.h"

/**
 * AI动画实例
 */
UCLASS()
class INFINITYBLADE_API UAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/** 人物的移动速度 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;
	/** 是否处于播放状态 */
	bool bIsPlaying;
public:
	/** 更新人物移动速度 */
	UFUNCTION(BlueprintCallable)
		void UpdateSpeed();
	/** 开始播放通知 */
	UFUNCTION()
		void AnimNotify_PlayStart(UAnimNotify* Notify);
	/** 结束播放通知 */
	UFUNCTION()
		void AnimNotify_PlayEnd(UAnimNotify* Notify);
	/** 死亡动画通知 */
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
};
