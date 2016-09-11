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
#include "EtherealAudioManager.h"


// Sets default values
AEtherealAudioManager::AEtherealAudioManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get Assets for Battle Music
	static ConstructorHelpers::FObjectFinder<USoundCue> StandardAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Standard.Battle_Standard'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BossAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Boss.Battle_Boss'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ZhanIntroAudioObject(TEXT("SoundCue'/Game/Audio/Party/Zhan_Intro_Cue.Zhan_Intro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ZhanBattleAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Zhan.Battle_Zhan'"));

	// Get Assets for Background Music
	static ConstructorHelpers::FObjectFinder<USoundCue> MainMenuAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_MainMenu.Music_MainMenu'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ArcadiaAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_Arcadia.Music_Arcadia'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ShiitakeAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_ShiitakeTemple.Music_ShiitakeTemple'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> VulcanAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_VulcanShrine.Music_VulcanShrine'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BorealAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_BorealCore.Music_BorealCore'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> YggdrasilAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_Yggdrasil.Music_Yggdrasil'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EmpyreanAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_EmpyreanGardens.Music_EmpyreanGardens'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CelestialAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_CelestialNexus.Music_CelestialNexus'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LevelUpAudioObject(TEXT("SoundCue'/Game/Audio/Music/LevelUp_Fanfare.LevelUp_Fanfare'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> StartGameAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_StartGame_Cue.Ethereal_StartGame_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SelectAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuSelect_Cue.Ethereal_MenuSelect_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SwitchAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuSwitch_Cue.Ethereal_MenuSwitch_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CursorAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuCursor_Cue.Ethereal_MenuCursor_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CancelAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuCancel_Cue.Ethereal_MenuCancel_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BindingAttachAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_Binding_Attach_Cue.Ethereal_Binding_Attach_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ErrorAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuError_Cue.Ethereal_MenuError_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> NPCNotifyAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_NPCNotify_Cue.Ethereal_NPCNotify_Cue'"));

	// Store audio objects
	S_Battle_Standard = StandardAudioObject.Object;
	S_Battle_Boss = BossAudioObject.Object;
	S_Zhan_Intro = ZhanIntroAudioObject.Object;
	S_Zhan_Battle = ZhanBattleAudioObject.Object;
	S_BGM_MainMenu = MainMenuAudioObject.Object;
	S_BGM_Arcadia = ArcadiaAudioObject.Object;
	S_BGM_Shiitake = ShiitakeAudioObject.Object;
	S_BGM_Vulcan = VulcanAudioObject.Object;
	S_BGM_Boreal = BorealAudioObject.Object;
	S_BGM_Yggdrasil = YggdrasilAudioObject.Object;
	S_BGM_Empyrean = EmpyreanAudioObject.Object;
	S_BGM_Celestial = CelestialAudioObject.Object;
	S_SFX_LevelUp = LevelUpAudioObject.Object;
	S_SFX_StartGame = StartGameAudioObject.Object;
	S_SFX_Select = SelectAudioObject.Object;
	S_SFX_Switch = SwitchAudioObject.Object;
	S_SFX_Cursor = CursorAudioObject.Object;
	S_SFX_Cancel = CancelAudioObject.Object;
	S_SFX_BindingAttach = BindingAttachAudioObject.Object;
	S_SFX_Error = ErrorAudioObject.Object;
	S_NPC_Notify = NPCNotifyAudioObject.Object;

	// Creates a scene component and sets it as the root
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	// Construct the CurrentAudio component
	CurrentAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("CurrentAudio"));

	// Construct Other Audio components
	Battle_Standard = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Battle_Standard"));
	Battle_Boss = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Battle_Boss"));
	Zhan_Intro = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Zhan_Intro"));
	Zhan_Battle = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Zhan_Battle"));
	BGM_MainMenu = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_MainMenu"));
	BGM_Arcadia = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Arcadia"));
	BGM_Shiitake = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Shiitake"));
	BGM_Vulcan = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Vulcan"));
	BGM_Boreal = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Boreal"));
	BGM_Yggdrasil = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Yggdrasil"));
	BGM_Empyrean = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Empyrean"));
	BGM_Celestial = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Celestial"));
	SFX_LevelUp = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_LevelUp"));
	SFX_StartGame = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_StartGame"));
	SFX_Select = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Select"));
	SFX_Switch = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Switch"));
	SFX_Cursor = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Cursor"));
	SFX_Cancel = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Cancel"));
	SFX_BindingAttach = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_BindingAttach"));
	SFX_Error = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Error"));
	NPC_Notify = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("NPC_Notify"));

	// Set Audio Objects to use their sound assets
	Battle_Standard->Sound = S_Battle_Standard;
	Battle_Boss->Sound = S_Battle_Boss;
	Zhan_Intro->Sound = S_Zhan_Intro;
	Zhan_Battle->Sound = S_Zhan_Battle;
	BGM_MainMenu->Sound = S_BGM_MainMenu;
	BGM_Arcadia->Sound = S_BGM_Arcadia;
	BGM_Shiitake->Sound = S_BGM_Shiitake;
	BGM_Vulcan->Sound = S_BGM_Vulcan;
	BGM_Boreal->Sound = S_BGM_Boreal;
	BGM_Yggdrasil->Sound = S_BGM_Yggdrasil;
	BGM_Empyrean->Sound = S_BGM_Empyrean;
	BGM_Celestial->Sound = S_BGM_Celestial;
	SFX_LevelUp->Sound = S_SFX_LevelUp;
	SFX_StartGame->Sound = S_SFX_StartGame;
	SFX_Select ->Sound = S_SFX_Select;
	SFX_Switch->Sound = S_SFX_Switch;
	SFX_Cursor->Sound = S_SFX_Cursor;
	SFX_Cancel->Sound = S_SFX_Cancel;
	SFX_BindingAttach->Sound = S_SFX_BindingAttach;
	SFX_Error->Sound = S_SFX_Error;
	NPC_Notify->Sound = S_NPC_Notify;

	// Deactivate all audio on construction
	CurrentAudio->bAutoActivate = false;
	Battle_Standard->bAutoActivate = false;
	Battle_Boss->bAutoActivate = false;
	Zhan_Intro->bAutoActivate = false;
	Zhan_Battle->bAutoActivate = false;
	BGM_MainMenu->bAutoActivate = false;
	BGM_Arcadia->bAutoActivate = false;
	BGM_Shiitake->bAutoActivate = false;
	BGM_Vulcan->bAutoActivate = false;
	BGM_Boreal->bAutoActivate = false;
	BGM_Yggdrasil->bAutoActivate = false;
	BGM_Empyrean->bAutoActivate = false;
	BGM_Celestial->bAutoActivate = false;
	SFX_LevelUp->bAutoActivate = false;
	SFX_StartGame->bAutoActivate = false;
	SFX_Select ->bAutoActivate = false;
	SFX_Switch->bAutoActivate = false;
	SFX_Cursor->bAutoActivate = false;
	SFX_Cancel->bAutoActivate = false;
	SFX_BindingAttach->bAutoActivate = false;
	SFX_Error->bAutoActivate = false;
	NPC_Notify->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEtherealAudioManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// BATTLE MUSIC FUNCTIONS

// Play the Battle Music, based on the selection type.
void AEtherealAudioManager::Play_BattleMusic(EBattleTypes Selection)
{
	switch (Selection)
	{
	case EBattleTypes::BT_Standard:
		Play_Battle_Standard();
		break;
	case EBattleTypes::BT_Boss:
		Play_Battle_Boss();
		break;
	case EBattleTypes::BT_ZhanIntro:
		Play_Zhan_Intro();
		break;
	case EBattleTypes::BT_ZhanBattle:
		Play_Zhan_Battle();
		break;
	}
}

// Play Standard Battle Music
void AEtherealAudioManager::Play_Battle_Standard()
{
	if (Battle_Standard->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio			
		}
		Battle_Standard->FadeIn(0.5f, 1);  // fade in the battle music
		//Battle_Standard->Play();  // Play the Standard Battle Music
		CurrentAudio = Battle_Standard;  // Set the current audio to be the Standard Battle Music
	}
}

// Play Boss Battle Music
void AEtherealAudioManager::Play_Battle_Boss()
{
	if (Battle_Boss->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		Battle_Boss->FadeIn(0.5f, 1);  // fade in the battle music
		//Battle_Boss->Play();  // Play the Standard Battle Music
		CurrentAudio = Battle_Boss;  // Set the current audio to be the Standard Battle Music
	}
}

// Play Zhan Intro Music
void AEtherealAudioManager::Play_Zhan_Intro()
{
	if (Zhan_Intro->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		Zhan_Intro->FadeIn(0.5f, 1);  // fade in the music
		//Zhan_Intro->Play();  // Play the Music
		CurrentAudio = Zhan_Intro;  // Set the current audio to be this Music
	}
}

// Play Zhan Battle Music
void AEtherealAudioManager::Play_Zhan_Battle()
{
	if (Zhan_Battle->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		Zhan_Battle->FadeIn(0.5f, 1);  // fade in the music
		//Zhan_Intro->Play();  // Play the Music
		CurrentAudio = Zhan_Battle;  // Set the current audio to be this Music
	}
}

// LEVEL BACKGROUND MUSIC FUNCTIONS

// Play Background Music, based on Level
void AEtherealAudioManager::Play_BGM(ERealms Level)
{
	switch (Level)
	{
	case ERealms::R_MainMenu:
		Play_BGM_MainMenu();
		break;
	case ERealms::R_Loading:

		break;
	case ERealms::R_Arcadia:
		Play_BGM_Arcadia();
		break;
	case ERealms::R_Shiitake:
		Play_BGM_Shiitake();
		break;
	case ERealms::R_Vulcan:
		Play_BGM_Vulcan();
		break;
	case ERealms::R_Boreal:
		Play_BGM_Boreal();
		break;
	case ERealms::R_Yggdrasil:
		Play_BGM_Yggdrasil();
		break;
	case ERealms::R_Empyrean:
		Play_BGM_Empyrean();
		break;
	case ERealms::R_Celestial:
		Play_BGM_Celestial();
		break;
	}
}

// Play Main Menu Background Music
void AEtherealAudioManager::Play_BGM_MainMenu()
{
	if (BGM_MainMenu->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_MainMenu->FadeIn(0.5f, 1);  // fade in the music
		//BGM_MainMenu->Play();  // Play the Music
		CurrentAudio = BGM_MainMenu;  // Set the current audio to be this Music
	}
}

// Play Arcadia Background Music
void AEtherealAudioManager::Play_BGM_Arcadia()
{
	if (BGM_Arcadia->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Arcadia->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Arcadia->Play();  // Play the Music
		CurrentAudio = BGM_Arcadia;  // Set the current audio to be this Music
	}
}

// Play Shiitake Temple Background Music
void AEtherealAudioManager::Play_BGM_Shiitake()
{
	if (BGM_Shiitake->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Shiitake->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Shiitake->Play();  // Play the Music
		CurrentAudio = BGM_Shiitake;  // Set the current audio to be this Music
	}
}

// Play Vulcan Shrine Background Music
void AEtherealAudioManager::Play_BGM_Vulcan()
{
	if (BGM_Vulcan->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Vulcan->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Vulcan->Play();  // Play the Music
		CurrentAudio = BGM_Vulcan;  // Set the current audio to be this Music
	}
}

// Play Boreal Core Background Music
void AEtherealAudioManager::Play_BGM_Boreal()
{
	if (BGM_Boreal->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Boreal->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Boreal->Play();  // Play the Music
		CurrentAudio = BGM_Boreal;  // Set the current audio to be this Music
	}
}

// Play Yggdrasil Background Music
void AEtherealAudioManager::Play_BGM_Yggdrasil()
{
	if (BGM_Yggdrasil->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Yggdrasil->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Yggdrasil->Play();  // Play the Music
		CurrentAudio = BGM_Yggdrasil;  // Set the current audio to be this Music
	}
}

// Play Empyrean Gardens Background Music
void AEtherealAudioManager::Play_BGM_Empyrean()
{
	if (BGM_Empyrean->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Empyrean->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Empyrean->Play();  // Play the Music
		CurrentAudio = BGM_Empyrean;  // Set the current audio to be this Music
	}
}

// Play Celestial Nexus Background Music
void AEtherealAudioManager::Play_BGM_Celestial()
{
	if (BGM_Celestial->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Celestial->FadeIn(0.5f, 1);  // fade in the music
		//BGM_Celestial->Play();  // Play the Music
		CurrentAudio = BGM_Celestial;  // Set the current audio to be this Music
	}
}

// SOUND EFFECTS FUNCTIONS

// Play Level Up Sound Effect
void AEtherealAudioManager::Play_SFX_LevelUp()
{
	SFX_LevelUp->Play();
}

// Play Start Game Menu SFX
void AEtherealAudioManager::Play_SFX_StartGame()
{
	SFX_StartGame->Play();
}

// Play Select Menu SFX
void AEtherealAudioManager::Play_SFX_Select()
{
	SFX_Select->Play();
}

// Play Switch Menu SFX
void AEtherealAudioManager::Play_SFX_Switch()
{
	SFX_Switch->Play();
}

// Play Cursor Menu SFX
void AEtherealAudioManager::Play_SFX_Cursor()
{
	SFX_Cursor->Play();
}

// Play Cancel Menu SFX
void AEtherealAudioManager::Play_SFX_Cancel()
{
	SFX_Cancel->Play();
}

// Play Binding Attach Menu SFX
void AEtherealAudioManager::Play_SFX_BindingAttach()
{
	SFX_BindingAttach->Play();
}

// Play Error Menu SFX
void AEtherealAudioManager::Play_SFX_Error()
{
	SFX_Error->Play();
}

// Play NPC Notify SFX
void AEtherealAudioManager::Play_NPC_Notify()
{
	NPC_Notify->Play();
}

// Play Targeting Notify SFX
void AEtherealAudioManager::Play_Target_Notify()
{
	SFX_Cursor->Play(); // plays the menu UI cursor audio
}