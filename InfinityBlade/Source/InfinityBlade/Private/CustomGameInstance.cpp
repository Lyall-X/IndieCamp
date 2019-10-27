// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameInstance.h"
//#include <MoviePlayer.h>

/** 初始化方法 */
void UCustomGameInstance::Init()
{
	UGameInstance::Init();

	/** 开始加载地图的委托 */
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCustomGameInstance::PreLoadMap);
	/** 结束加载地图的委托 */
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UCustomGameInstance::PostLoadMap);
	/** 初始化 */
	LoadWidget = CreateWidget<ULoadUserWidget>(this, LoadClass<ULoadUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoadWidget.BP_LoadWidget_C'")));
}

/** 地图加载开始的方法 */
void UCustomGameInstance::PreLoadMap(const FString& Map)
{
	/** 判断是否是加载的主关卡 */
	if (Map.Equals("/Game/Map/Map_Main"))
	{
		/** 创建一个屏幕加载属性对象 */
		FLoadingScreenAttributes LoadingAttr;
		/** 手动的点击跳过加载 */
		LoadingAttr.bWaitForManualStop = true;
		/** 设置加载的Widget */
		LoadingAttr.WidgetLoadingScreen = LoadWidget->TakeWidget();
		/** 设置加载屏幕 */
		GetMoviePlayer()->SetupLoadingScreen(LoadingAttr);
	}
}

/** 地图加载结束的方法 */
void UCustomGameInstance::PostLoadMap(UWorld* World)
{

}

/** 是否加载完成 */
bool UCustomGameInstance::GetLoadStatus()
{
	/** 返回是否已经加载完成 */
	return GetMoviePlayer()->IsLoadingFinished();
}
