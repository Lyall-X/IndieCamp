// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/XCharacter.h"
#include "XPlayerController.generated.h"

/**
 * 主角英雄的控制器
 */
UCLASS()
class INFINITYBLADE_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** 英雄角色对象 */
	UPROPERTY()
		AXCharacter * XCharacter;


public:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
	/** 绑定输入控件 */
	virtual void SetupInputComponent() override;


public:
	/** 前后移动 */
	UFUNCTION()
		void MoveForward(float Speed);
	/** 左右移动 */
	UFUNCTION()
		void MoveRight(float Speed);
};
