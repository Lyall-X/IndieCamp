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

public:
	/** 更新人物移动速度 */
	UFUNCTION(BlueprintCallable)
		void UpdateSpeed();
};
