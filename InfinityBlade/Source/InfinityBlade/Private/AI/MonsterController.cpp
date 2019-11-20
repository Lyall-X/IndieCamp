// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "AI/AICharacter.h"


/** 构造方法 */
AMonsterController::AMonsterController()
{
	/** 初始化行为树控件 */
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	/** 初始化黑板控件 */
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

/** 重写控制的方法 */
void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	/** 初始化AI类 */
	AAICharacter* Monster = Cast<AAICharacter>(InPawn);
	///** 初始化动画实例 */
	//AnimInstance = Cast<UAIAnimInstance>(Monster->GetMesh()->GetAnimInstance());

	///** 判断武器类是否有效 */
	//if (Monster->AIWeaponClass)
	//{
	//	/** 生成一个武器对象 */
	//	AIWeapon = GetWorld()->SpawnActor<AWeapon>(Monster->AIWeaponClass);
	//	/** 绑定规则 */
	//	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	//	/** 绑定武器 */
	//	AIWeapon->AttachToComponent(Monster->GetMesh(), AttachmentRules, TEXT("hand_rSocket"));
	//	/** 绑定武器重叠事件 */
	//	AIWeapon->CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonsterController::WeaponOverlapDamage);
	//}

	/** 判断行为树控件 */
	if (Monster->BehaviorTree)
	{
		/** 初始化黑板 */
		BlackboardComponent->InitializeBlackboard(*((Monster->BehaviorTree->BlackboardAsset)));
		/** 启动行为树 */
		BehaviorTreeComponent->StartTree(*(Monster->BehaviorTree));
	}
}