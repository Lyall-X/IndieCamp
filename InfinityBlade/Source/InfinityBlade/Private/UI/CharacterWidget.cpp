// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWidget.h"

/** 重写按钮初始化方法 */
bool UCharacterWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** 初始化关闭按钮 */
	BtnClose = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));
	/** 绑定点击事件 */
	BtnClose->OnClicked.AddDynamic(this, &UCharacterWidget::CloseBtnOnClickedEvent);
	/** 初始化滚动盒子 */
	ScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBoxBag")));

	return true;
}

/** 关闭按钮点击事件 */
void UCharacterWidget::CloseBtnOnClickedEvent()
{
	this->RemoveFromViewport();
}
