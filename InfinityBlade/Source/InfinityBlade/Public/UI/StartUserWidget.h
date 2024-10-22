// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "StartUserWidget.generated.h"

/**
 * 游戏开始界面
 */
UCLASS()
class INFINITYBLADE_API UStartUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 开始游戏按钮 */
	UPROPERTY()
		UButton* StartBtn;
	/** 注册账号按钮 */
	UPROPERTY()
		UButton* RegisterBtn;
	/** 退出游戏按钮 */
	UPROPERTY()
		UButton* QuitBtn;

public:
	/** 控件创建完成后初始化方法 */
	virtual bool Initialize() override;
	/** 退出游戏按钮点击事件 */
	//只有加入uFunction才会纳入UE4整体框架树，不然没办法识别这个回调函数
	UFUNCTION()
		void QuitBtnOnClickedEvent();
};
