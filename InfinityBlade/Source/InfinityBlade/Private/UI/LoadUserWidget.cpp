// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadUserWidget.h"

/** 控件创建完成初始化方法 */
bool ULoadUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/** 初始化进度条 */
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("CircularThrobber_Load")));
	/** 初始化加载文本 */
	LoadingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Load")));
	/** 初始化继续按钮 */
	NextText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Next")));

	return true;
}