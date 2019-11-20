// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAnimInstance.h"

/** 更新人物移动速度 */
void UAIAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}