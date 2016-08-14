// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "Temperance.h"

// Sets default values
ATemperance::ATemperance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blunt/Blunt_Temperance/SK_Temperance.SK_Temperance'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_Temperance.WeaponIcon_Temperance'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_Temperance-small.WeaponIcon_Temperance-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_Temperance;
	Type = EMasterGearTypes::GT_TwoHanded;
	Description = "One of the seven Ethereal Virtues.";
	MPCost = 0.0f;
	ATK = 50.0f;
	DEF = 60.0f;
	SPD = 25.0f;
	HP = 500.0f;
	MP = 100.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	WeaponSkeletalMesh->SetVisibility(true);
	SwordCollider->SetBoxExtent(FVector(20.0f, 30.0f, 55.0f));
	SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
}

// Called when the game starts or when spawned
void ATemperance::BeginPlay()
{
	Super::BeginPlay();
}

