// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CircularThrobber.h"
#include "Components/TextBlock.h"
#include "LoadUserWidget.generated.h"

/**
 * 加载UI
 */
UCLASS()
class INFINITYBLADE_API ULoadUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** 加载进度条 */
	UPROPERTY()
		UCircularThrobber* CircularThrobber;
	/** 加载文本 */
	UPROPERTY()
		UTextBlock* LoadingText;
	/** 继续按钮 */
	UPROPERTY()
		UTextBlock* NextText;
public:
	/** 控件创建完成初始化方法 */
	virtual bool Initialize() override;
};
