// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UI/StartUserWidget.h"
#include "UI/LoginUserWidget.h"
#include "UI/RegisterUserWidget.h"
#include "StartGameMode.generated.h"

/**
 * 开始游戏模式类
 */
UCLASS()
class INFINITYBLADE_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/** 游戏开始界面 */
	UPROPERTY()
		UStartUserWidget* StartWidget;
	/** 游戏登录界面 */
	UPROPERTY()
		ULoginUserWidget* LoginWidget;
	/** 游戏注册界面 */
	UPROPERTY()
		URegisterUserWidget* RegisterWidget;

public:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
	/** 开始游戏按钮点击事件 */
	UFUNCTION()
		void StartBtnOnClickedEvent();
	/** 注册账号按钮点击事件 */
	UFUNCTION()
		void RegisterBtnOnClickedEvent();
	/** 登录页面返回按钮点击事件 */
	UFUNCTION()
		void LoginBackBtnOnClickedEvent();
	/** 注册页面返回按钮点击事件 */
	UFUNCTION()
		void RegisterBackBtnOnClickedEvent();
};
