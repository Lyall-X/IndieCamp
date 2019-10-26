// Fill out your copyright notice in the Description page of Project Settings.

#include "StartUserWidget.h"

/** 控件创建完成后初始化方法 */
bool UStartUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/** 初始化游戏开始按钮 */
	StartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));
	/** 初始化注册账号按钮 */
	RegisterBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Register")));
	/** 初始化退出游戏按钮 */
	QuitBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	/** 退出游戏按钮点击事件 */
	QuitBtn->OnClicked.AddDynamic(this, &UStartUserWidget::QuitBtnOnClickedEvent);

	return true;
}

/** 退出游戏按钮点击事件 */
void UStartUserWidget::QuitBtnOnClickedEvent()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

