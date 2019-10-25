// Fill out your copyright notice in the Description page of Project Settings.

#include "StartGameMode.h"

/** 游戏开始调用的方法 */
void AStartGameMode::BeginPlay()
{
	/** 初始化游戏开始界面 */
	StartWidget = CreateWidget<UStartUserWidget>(GetGameInstance(), LoadClass<UStartUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_StartUserWidget.BP_StartUserWidget_C'")));
	/** 添加到视口 */
	StartWidget->AddToViewport();

	/** 开始游戏按钮的点击事件 */
	StartWidget->StartBtn->OnClicked.AddDynamic(this, &AStartGameMode::StartBtnOnClickedEvent);
	/** 注册账号按钮的点击事件 */
	StartWidget->RegisterBtn->OnClicked.AddDynamic(this, &AStartGameMode::RegisterBtnOnClickedEvent);
	
	/** 初始化游戏登录界面 */
	LoginWidget = CreateWidget<ULoginUserWidget>(GetGameInstance(), LoadClass<ULoginUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoginUserWidget.BP_LoginUserWidget_C'")));
	/** 设置登录界面返回按钮的点击事件 */
	LoginWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::LoginBackBtnOnClickedEvent);

	/** 初始化注册账号界面 */
	RegisterWidget = CreateWidget<URegisterUserWidget>(GetGameInstance(), LoadClass<URegisterUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_RegisterUserWidget.BP_RegisterUserWidget_C'")));
	/** 设置注册界面返回按钮的点击事件 */
	RegisterWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::RegisterBackBtnOnClickedEvent);
}

/** 开始游戏按钮点击事件 */
void AStartGameMode::StartBtnOnClickedEvent()
{
	/** 游戏开始界面从视口中移除 */
	StartWidget->RemoveFromViewport();
	/** 登录游戏界面添加到视口 */
	LoginWidget->AddToViewport();
}

/** 注册账号按钮点击事件 */
void AStartGameMode::RegisterBtnOnClickedEvent()
{
	/** 游戏开始界面从视口中移除 */
	StartWidget->RemoveFromViewport();
	/** 注册账号界面添加到视口中 */
	RegisterWidget->AddToViewport();
}

/** 登录页面返回按钮点击事件 */
void AStartGameMode::LoginBackBtnOnClickedEvent()
{
	/** 登录账号界面从视口中移除 */
	LoginWidget->RemoveFromViewport();
	/** 游戏开始界面添加到视口当中 */
	StartWidget->AddToViewport();
}

/** 注册页面返回按钮点击事件 */
void AStartGameMode::RegisterBackBtnOnClickedEvent()
{
	/** 注册账号界面从视口中移除 */
	RegisterWidget->RemoveFromViewport();
	/** 游戏开始界面添加到视口当中 */
	StartWidget->AddToViewport();
}
