// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "ValhallaFlanchard.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AValhallaFlanchard::AValhallaFlanchard(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ValhallaFlanchard.ArmorIcon_ValhallaFlanchard'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ValhallaFlanchard-small.ArmorIcon_ValhallaFlanchard-small'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	
	// Set Default Values
	Name = EMasterGearList::GL_ValhallaFlanchard;
	NameText = LOCTEXT("ValhallaFlanchardText", "Valhalla Flanchard");
	Type = EMasterGearTypes::GT_Legs;
	Description = "A construct of the Ethereal Order, the armor draws energy from the dead to grant power the living.";
	MPCost = 0;
	ATK = 10;
	DEF = 10;
	SPD = 5;
	HP = 100;
	MP = 50;
}

// Called when the game starts or when spawned
void AValhallaFlanchard::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE