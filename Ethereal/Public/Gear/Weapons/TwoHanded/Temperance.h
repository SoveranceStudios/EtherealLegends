// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/Weapons/Weapon_Master.h"
#include "Temperance.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API ATemperance : public AWeapon_Master
{
	GENERATED_BODY()
	
public:

	ATemperance(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	UBoxComponent* SwordCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollider"));	
};
