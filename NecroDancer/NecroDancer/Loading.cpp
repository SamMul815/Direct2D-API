#include "stdafx.h"
#include "Loading.h"


Loading::Loading()
{
}


Loading::~Loading()
{
}


HRESULT Loading::Init()
{
	
	_count = 0;	//이미지 한장씩 불러와야되니까....
	SOUNDMANAGER->AddSound("Loading", ".\\Sound\\Stage\\Loading.ogg", 0.5, TRUE);
	IMAGEMANAGER->AddImage("LoadingScene", L".\\Image\\GameUI\\mainmenu.png", WINSIZEX, WINSIZEY-100);
	IMAGEMANAGER->AddImage("LoadingSkeletonBase", L".\\Image\\Enemy\\Loadingskeleton.png", 576, 150, 8, 2);
	IMAGEMANAGER->AddImage("ClearSkeletonBase", L".\\Image\\GameUI\\skeletonClear.png", 1536, 400, 8, 1);
	IMAGEMANAGER->AddImage("Press",L".\\Image\\GameUI\\press.png", 360, 60);

	SOUNDMANAGER->Play("Loading", 1.0f);
	return S_OK;
}

void Loading::Update()
{
		_count++;

	switch(_count)
	{

	case 1:  SOUNDMANAGER->AddSound("Stage1", ".\\Sound\\Stage\\zone1_1.ogg", 0.5, FALSE);																		break;
	case 2 : SOUNDMANAGER->AddSound("Stage1Shop", ".\\Sound\\ShopKeeper\\zone1_1_shopkeeper.ogg", 0.5, FALSE);													break;
	case 3 : SOUNDMANAGER->AddSound("Stage2", ".\\Sound\\Stage\\zone1_2.ogg", 0.5, FALSE);																		break;
	case 4 : SOUNDMANAGER->AddSound("Stage2Shop", ".\\Sound\\ShopKeeper\\zone1_2_shopkeeper.ogg", 0.5, FALSE);													break;
	case 5 : SOUNDMANAGER->AddSound("Stage3", ".\\Sound\\Stage\\zone1_3.ogg", 0.5, FALSE);																		break;
	case 6 : SOUNDMANAGER->AddSound("Stage3Shop", ".\\Sound\\ShopKeeper\\zone1_3_shopkeeper.ogg", 0.5, FALSE);													break;
	case 7 : 																																					break;
	case 8 :  //효과음 불러오기 - 적 관련																															break;
	case 9 :  SOUNDMANAGER->AddSound("ChestOpen", ".\\Sound\\Effect\\chestOpen.ogg", 1.0f, FALSE);																break;
	case 10 : SOUNDMANAGER->AddSound("SlimeAttack", ".\\Sound\\Effect\\en_slime_attack.ogg", 1.0f, FALSE);														break;
	case 11 : SOUNDMANAGER->AddSound("SlimeDeath", ".\\Sound\\Effect\\en_slime_death.ogg", 1.0f, FALSE);														break;
	case 12 : 																																					break;
	case 13 : SOUNDMANAGER->AddSound("Dragon_Attack", ".\\Sound\\Effect\\dragon_attack_melee.ogg", 1.0f, FALSE);												break;
	case 14 : SOUNDMANAGER->AddSound("Dragon_Hit", ".\\Sound\\Effect\\dragon_hit.ogg", 1.0f, FALSE);															break;
	case 15 : SOUNDMANAGER->AddSound("Dragon_Cry", ".\\Sound\\Effect\\dragon_cry.ogg", 1.0f, FALSE);															break;
	case 16 : SOUNDMANAGER->AddSound("Dragon_Walk", ".\\Sound\\Effect\\dragon_walk.ogg", 1.0f, FALSE);															break;
	case 17 : SOUNDMANAGER->AddSound("Dragon_Death", ".\\Sound\\Effect\\dragon_death.ogg", 1.0f, FALSE);														break;
	case 18 : 																																					break;
	case 19 : SOUNDMANAGER->AddSound("DigFail", ".\\Sound\\Effect\\digFail.ogg", 1.0f, FALSE);																	break;
	case 20 : SOUNDMANAGER->AddSound("DigOK", ".\\Sound\\Effect\\digOK.ogg", 1.0f, FALSE);																		break;
	case 21 : SOUNDMANAGER->AddSound("PlayerDeath", ".\\Sound\\Effect\\PlayerDeath.ogg", 1.0f, FALSE);															break;
	case 22 : SOUNDMANAGER->AddSound("PlayerAttack1", ".\\Sound\\Effect\\vo_ari_melee_1_01.ogg", 1.0f, FALSE);													break;
	case 23 : SOUNDMANAGER->AddSound("PlayerAttack2", ".\\Sound\\Effect\\vo_ari_melee_1_02.ogg", 1.0f, FALSE);													break;
	case 24 : SOUNDMANAGER->AddSound("PlayerAttack3", ".\\Sound\\Effect\\vo_ari_melee_1_03.ogg", 1.0f, FALSE);													break;
	case 25 : SOUNDMANAGER->AddSound("PlayerAttack4", ".\\Sound\\Effect\\vo_ari_melee_1_04.ogg", 1.0f, FALSE);													break;
	case 26 : SOUNDMANAGER->AddSound("PlayerAttack5", ".\\Sound\\Effect\\vo_ari_melee_1_05.ogg", 1.0f, FALSE);													break;
	case 27 : SOUNDMANAGER->AddSound("PlayerBat", ".\\Sound\\Effect\\sfx_shrine_sacrifice.ogg", 1.0f, FALSE);																																					break;
	case 28 : 																																					break;
	case 29 : SOUNDMANAGER->AddSound("SpellFire_voice", ".\\Sound\\Effect\\vo_ari_castspell_fire.ogg", 1.0f, FALSE);											break;
	case 30 : SOUNDMANAGER->AddSound("SpellFire", ".\\Sound\\Effect\\wep_spell_general_ST.ogg", 1.0f, FALSE);													break;
	case 31 : 																																					break;
	case 32 : SOUNDMANAGER->AddSound("SpellHeal_voice", ".\\Sound\\Effect\\vo_ari_heal_01.ogg", 1.0f, FALSE);													break;
	case 33 : SOUNDMANAGER->AddSound("SpellHeal", ".\\Sound\\Effect\\wep_spell_heal.ogg", 1.0f, FALSE);															break;
	case 34 : 																																					break;
	case 35 : SOUNDMANAGER->AddSound("PlayerHit1", ".\\Sound\\Effect\\vo_ari_hurt_01.ogg", 1.0f, FALSE);														break;
	case 36 : SOUNDMANAGER->AddSound("PlayerHit2", ".\\Sound\\Effect\\vo_ari_hurt_02.ogg", 1.0f, FALSE);														break;
	case 37 : SOUNDMANAGER->AddSound("PlayerHit3", ".\\Sound\\Effect\\vo_ari_hurt_03.ogg", 1.0f, FALSE);														break;
	case 38 : SOUNDMANAGER->AddSound("PlayerHitSFX", ".\\Sound\\Effect\\sfx_player_hit_ST.ogg", 1.0f, FALSE);													break;
	case 39 : SOUNDMANAGER->AddSound("PlayerDeath", ".\\Sound\\Effect\\vo_ari_death_01.ogg", 1.0f, FALSE);																																						break;
	case 40 : SOUNDMANAGER->AddSound("PlayerDig1", ".\\Sound\\Effect\\vo_ari_dig_01.ogg", 1.0f, FALSE);															break;
	case 41 : SOUNDMANAGER->AddSound("PlayerDig2", ".\\Sound\\Effect\\vo_ari_dig_02.ogg", 1.0f, FALSE);															break;
	case 42 : SOUNDMANAGER->AddSound("PlayerDig3", ".\\Sound\\Effect\\vo_ari_dig_03.ogg", 1.0f, FALSE);															break;
	case 43 : 																																					break;
	case 44 : SOUNDMANAGER->AddSound("TrapBounce", ".\\Sound\\Effect\\trapBounce.ogg", 1.0f, FALSE);															break;
	case 45 : SOUNDMANAGER->AddSound("TrapNeedle", ".\\Sound\\Effect\\trapNeedle.ogg", 1.0f, FALSE);															break;
	case 46 : 																																					break;
	case 47 : //이미지 불러오기 -플레이어																															break;
	case 48 : IMAGEMANAGER->AddImage("PlayerHead", L".\\Image\\Player\\player1_heads.png", 94, 48, 4, 2);														break;
	case 49 : IMAGEMANAGER->AddImage("PlayerBody", L".\\Image\\Player\\player1_armor_body.png", 94, 204, 4, 10);												break;
	case 50 : 																																					break;
	case 51 : //이미지 불러오기 -몬스터																																break;
	case 52 : IMAGEMANAGER->AddImage("SlimeGreen", L".\\Image\\Enemy\\slime_green.png", 104, 52, 4, 2);															break;
	case 53 : IMAGEMANAGER->AddImage("SlimeIce", L".\\Image\\Enemy\\slime_ice.png", 104, 52, 4, 2);																break;
	case 54 : IMAGEMANAGER->AddImage("SlimeFire", L".\\Image\\Enemy\\slime_fire.png", 104, 52, 4, 2);															break;
	case 55 : IMAGEMANAGER->AddImage("SkeletonBase", L".\\Image\\Enemy\\skeleton.png", 192, 50, 8, 2);															break;
	case 56 : IMAGEMANAGER->AddImage("SkeletonArmored", L".\\Image\\Enemy\\armoredskeleton.png", 144, 48, 6, 2);												break;
	case 57 : //IMAGEMANAGER->AddImage("SkeletonKnight", L".\\Image\\Enemy\\skeletonknight.png", 144, 84, 4, 2);												break;
	case 58 : //IMAGEMANAGER->AddImage("MonekyBase", L".\\Image\\Enemy\\monkey_white.png", 150, 48, 6, 2);														break;
	case 59 : //IMAGEMANAGER->AddImage("MonkeyYellow", L".\\Image\\Enemy\\monkey_yellow.png", 150, 48, 6, 2);													break;
	case 60 : //IMAGEMANAGER->AddImage("BatBase", L".\\Image\\Enemy\\bat.png", 96, 48, 4, 2);																	break;
	case 61 : //IMAGEMANAGER->AddImage("GoblinBase", L".\\Image\\Enemy\\goblin_bomber.png", 104, 72, 4, 2);														break;
	case 62 : //IMAGEMANAGER->AddImage("Minotaur", L".\\Image\\Enemy\\minotaur.png", 450, 98, 9, 2);															break;
	case 63 : IMAGEMANAGER->AddImage("DragonGreen", L".\\Image\\Enemy\\dragon_green.png", 108, 102, 2, 2);														break;
	case 64 : //IMAGEMANAGER->AddImage("DragonBlue", L".\\Image\\Enemy\\dragon_blue.png", 427, 102, 7, 2);														break;
	case 65 : IMAGEMANAGER->AddImage("ChestBase", L".\\Image\\Enemy\\chest.png", 24, 48, 1, 2);																	break;
	case 66 : IMAGEMANAGER->AddImage("ShopKeeper", L".\\Image\\Enemy\\shopkeeper.png", 376, 76, 8, 2);															break;
	case 67 : 																																					break;
	case 68 : 																																					break;
	case 69 : //이미지 불러오기 - 몬스터UI																															break;
	case 70 : IMAGEMANAGER->AddImage("Enemy_Heart", L".\\Image\\GameUI\\TEMP_heart_small.png", 12, 12);															break;
	case 71 : IMAGEMANAGER->AddImage("Enemy_Heart_Empty", L".\\Image\\GameUI\\TEMP_heart_empty_small.png", 12, 12);												break;
	case 72 : 																																					break;
	case 73 : //이미지 불러오기 -블럭 , 타일																														break;
	case 74 : IMAGEMANAGER->AddImage("Block", L".\\Image\\Object\\Stage1_BLOCK.png", 504, 48, 21, 1);															break;
	case 75 : IMAGEMANAGER->AddImage("Tile", L".\\Image\\Tile\\Stage1_TILE.png", 78, 52, 3, 2);																	break;
	case 76 : IMAGEMANAGER->AddImage("Stair", L".\\Image\\Object\\stair.png", 48, 24, 2, 1);																	break;
	case 77 : 																																					break;
	case 78 : //이미지 불러오기 -함정																																break;
	case 79 : IMAGEMANAGER->AddImage("BombTrap", L".\\Image\\Object\\bombtrap.png", 28, 32, 2, 2);																break;
	case 80 : IMAGEMANAGER->AddImage("MoveTrap", L".\\Image\\Object\\bouncetrap.png", 28, 96, 2, 6);															break;
	case 81 : IMAGEMANAGER->AddImage("NeedleTrap", L".\\Image\\Object\\spiketrap.png", 34, 120, 1, 6);															break;
	case 82 : IMAGEMANAGER->AddImage("TeleportTrap", L".\\Image\\Object\\teleporttrap.png", 28, 32, 2, 2);														break;
	case 83 : 																																					break;
	case 84 : //이미지 불러오기 -제단																																break;
	case 85 : IMAGEMANAGER->AddImage("BloodAltar", L".\\Image\\Object\\shrine_blood.png", 70, 104, 2, 2);														break;
	case 86 : IMAGEMANAGER->AddImage("DiceAltar", L".\\Image\\Object\\shrine_chance.png", 70, 104, 2, 2);														break;
	case 87 : IMAGEMANAGER->AddImage("SkullAltar", L".\\Image\\Object\\shrine_war.png", 70, 104, 2, 2);															break;
	case 88 : IMAGEMANAGER->AddImage("GlassAltar", L".\\Image\\Object\\shrine_glass.png", 70, 104, 2, 2);														break;
	case 89 : 																																					break;
	case 90 : //이미지 불러오기 UI																																	break;
	case 91 : IMAGEMANAGER->AddImage("Slot_Shovel", L".\\Image\\GameUI\\hud_slot_1.png", 30, 33);																break;
	case 92 : IMAGEMANAGER->AddImage("Slot_Weapon", L".\\Image\\GameUI\\hud_slot_2.png", 30, 33);																break;
	case 93 : IMAGEMANAGER->AddImage("Slot_Body", L".\\Image\\GameUI\\hud_slot_3.png", 30, 33);																	break;
	case 94 : IMAGEMANAGER->AddImage("Slot_Head", L".\\Image\\GameUI\\hud_slot_4.png", 30, 33);																	break;
	case 95 : IMAGEMANAGER->AddImage("Slot_Torch", L".\\Image\\GameUI\\hud_slot_6.png", 30, 33);																break;
	case 96 : IMAGEMANAGER->AddImage("Slot_Spell1", L".\\Image\\GameUI\\hud_slot_spell1.png", 32, 42);															break;
	case 97 : IMAGEMANAGER->AddImage("Slot_Spell2", L".\\Image\\GameUI\\hud_slot_spell2.png", 32, 42);															break;
	case 98 : IMAGEMANAGER->AddImage("10Kill", L".\\Image\\GameUI\\10kill.png", 22, 7);																			break;
	case 99 : IMAGEMANAGER->AddImage("5Kill", L".\\Image\\GameUI\\5kill.png", 22, 7);																																						break;
	case 100 : IMAGEMANAGER->AddImage("BeatNote", L".\\Image\\GameUI\\Note.png", 24, 64, 2, 1);																	break;
	case 101 : IMAGEMANAGER->AddImage("Heart", L".\\Image\\GameUI\\heart.png", 164, 105, 2, 1);																	break;
	case 102 : IMAGEMANAGER->AddImage("BlackBar", L".\\Image\\GameUI\\BeatBlack.png", 1200, 104);																break;
	case 103 : 																																					break;
	case 104 : //이미지 불러오기 플레이어 체력																														break;
	case 105 : IMAGEMANAGER->AddImage("Heart_Empty", L".\\Image\\GameUI\\heart_empty.png", 30, 33);																break;
	case 106 : IMAGEMANAGER->AddImage("Heart_Half", L".\\Image\\GameUI\\heart_half.png", 30, 33);																break;
	case 107 : IMAGEMANAGER->AddImage("Heart_Full", L".\\Image\\GameUI\\heart_full.png", 30, 33);																break;
	case 108 : 																																					break;
	case 109 : //아이템 이미지 불러오기 아이템																														break;
	case 110 : IMAGEMANAGER->AddImage("Body_1", L".\\Image\\ITEM\\body\\armor_1.png", 24, 48, 1, 2);															break;
	case 111 : IMAGEMANAGER->AddImage("Body_2", L".\\Image\\ITEM\\body\\armor_2.png", 24, 48, 1, 2);															break;
	case 112 : IMAGEMANAGER->AddImage("Body_3", L".\\Image\\ITEM\\body\\armor_3.png", 24, 48, 1, 2);															break;
	case 113 : IMAGEMANAGER->AddImage("Body_4", L".\\Image\\ITEM\\body\\armor_4.png", 24, 48, 1, 2);															break;
	case 114 : IMAGEMANAGER->AddImage("Body_5", L".\\Image\\ITEM\\body\\armor_5.png", 24, 48, 1, 2);															break;
	case 115 : 																																					break;
	case 116 : //아이템 이미지 불러오기 삽																															break;
	case 117 : IMAGEMANAGER->AddImage("Shovel_Base", L".\\Image\\ITEM\\shovel\\shovel_basic.png", 24, 48, 1, 2);												break;
	case 118 : IMAGEMANAGER->AddImage("Shovel_Blood", L".\\Image\\ITEM\\shovel\\shovel_blood.png", 24, 48, 1, 2);												break;
	case 119 : IMAGEMANAGER->AddImage("Shovel_Crystal", L".\\Image\\ITEM\\shovel\\shovel_crystal.png", 24, 48, 1, 2);											break;
	case 120 : IMAGEMANAGER->AddImage("Shovel_titanium", L".\\Image\\ITEM\\shovel\\shovel_titanium.png", 24, 48, 1, 2);											break;
	case 121 : 																																					break;
	case 122 : //아이템 이미지 불러오기 무기																														break;
	case 123 : IMAGEMANAGER->AddImage("Weapon_dagger", L".\\Image\\ITEM\\weapon\\weapon_dagger.png", 24, 48, 1, 2);												break;
	case 124 : IMAGEMANAGER->AddImage("Weapon_dagger_blood", L".\\Image\\ITEM\\weapon\\weapon_dagger_blood.png", 24, 48, 1, 2);									break;
	case 125 : IMAGEMANAGER->AddImage("Weapon_longsword", L".\\Image\\ITEM\\weapon\\weapon_longsword.png", 24, 48, 1, 2);										break;
	case 126 : IMAGEMANAGER->AddImage("Weapon_longsword_blood", L".\\Image\\ITEM\\weapon\\weapon_longsword_blood.png", 24, 48, 1, 2);							break;
	case 127 : IMAGEMANAGER->AddImage("Weapon_broadsword", L".\\Image\\ITEM\\weapon\\weapon_broadsword.png", 24, 48, 1, 2);										break;
	case 128 : IMAGEMANAGER->AddImage("Weapon_broadsword_blood", L".\\Image\\ITEM\\weapon\\weapon_broadsword_blood.png", 24, 48, 1, 2);							break;
	case 129 : 																																					break;
	case 130 : //아이템 이미지 불러오기 횃불																														break;
	case 131 : IMAGEMANAGER->AddImage("Torch_1", L".\\Image\\ITEM\\etc\\torch_1.png", 24, 48, 1, 2);															break;
	case 132 : IMAGEMANAGER->AddImage("Torch_2", L".\\Image\\ITEM\\etc\\torch_3.png", 24, 48, 1, 2);															break;
	case 133 : IMAGEMANAGER->AddImage("Torch_3", L".\\Image\\ITEM\\etc\\torch_foresight.png", 24, 48, 1, 2);													break;
	case 144 : 																																					break;
	case 155 : //이펙트 무기 효과																																	break;
	case 166 : IMAGEMANAGER->AddImage("Effect_dagger1", L".\\Image\\ITEM\\effect\\swipe_dagger1.png", 72, 24, 3, 1);											break;
	case 177 : IMAGEMANAGER->AddImage("Effect_dagger_blood1", L".\\Image\\ITEM\\effect\\swipe_dagger_blood1.png", 72, 24, 3, 1);								break;
	case 188 : IMAGEMANAGER->AddImage("Effect_longsword1", L".\\Image\\ITEM\\effect\\swipe_longsword1.png", 192, 24, 4, 1);										break;
	case 189 : IMAGEMANAGER->AddImage("Effect_longsword_blood1", L".\\Image\\ITEM\\effect\\swipe_longsword_blood1.png", 192, 24, 4, 1);							break;
	case 190 : IMAGEMANAGER->AddImage("Effect_broadsword1", L".\\Image\\ITEM\\effect\\swipe_broadsword1.png", 72, 72, 3, 1);									break;
	case 191 : IMAGEMANAGER->AddImage("Effect_broadsword_blood1", L".\\Image\\ITEM\\effect\\swipe_broadsword_blood1.png", 72, 72, 3, 1);						break;
	case 192 : 																																					break;
	case 193 : IMAGEMANAGER->AddImage("Effect_dagger2", L".\\Image\\ITEM\\effect\\swipe_dagger2.png", 24, 72, 1, 3);											break;
	case 194 : IMAGEMANAGER->AddImage("Effect_dagger_blood2", L".\\Image\\ITEM\\effect\\swipe_dagger_blood2.png", 24, 72, 1, 3);								break;
	case 195 : IMAGEMANAGER->AddImage("Effect_longsword2", L".\\Image\\ITEM\\effect\\swipe_longsword2.png", 24, 192, 1, 4);										break;
	case 196 : IMAGEMANAGER->AddImage("Effect_longsword_blood2", L".\\Image\\ITEM\\effect\\swipe_longsword_blood2.png", 24, 192, 1, 4);							break;
	case 197 : IMAGEMANAGER->AddImage("Effect_broadsword2", L".\\Image\\ITEM\\effect\\swipe_broadsword2.png", 72, 72, 1, 3);									break;
	case 198 : IMAGEMANAGER->AddImage("Effect_broadsword_blood2", L".\\Image\\ITEM\\effect\\swipe_broadsword_blood2.png", 72, 72, 1, 3);						break;
	case 199 : 																																					break;
	case 200 : //아이템 이미지 불러오기 머리																														break;
	case 201 : IMAGEMANAGER->AddImage("Head_Helmet", L".\\Image\\ITEM\\head\\head_helmet.png", 24, 48, 1, 2);													break;
	case 202 : IMAGEMANAGER->AddImage("Head_Crown", L".\\Image\\ITEM\\head\\head_crown_of_thorns.png", 24, 48, 1, 2);											break;
	case 203 : IMAGEMANAGER->AddImage("Head_Blast", L".\\Image\\ITEM\\head\\head_blast_helmet.png", 24, 48, 1, 2);												break;
	case 204 : IMAGEMANAGER->AddImage("Head_Miners", L".\\Image\\ITEM\\head\\head_miners_cap.png", 24, 48, 1, 2);												break;
	case 205 : 																																					break;
	case 206 : //이미지 불러오기 스킬																																break;
	case 207 : IMAGEMANAGER->AddImage("Spell_Fire", L".\\Image\\ITEM\\spell\\spell_fireball.png", 24, 48, 1, 2);												break;
	case 208 : IMAGEMANAGER->AddImage("Spell_Fire_Effect", L".\\Image\\ITEM\\spell\\fire1.png", 168, 24, 7, 1);													break;
	case 209 : IMAGEMANAGER->AddImage("Spell_Heal", L".\\Image\\ITEM\\spell\\spell_heal.png", 25, 48, 1, 2);													break;
	case 210 : //특수효과																																		    break;
	case 211 : IMAGEMANAGER->AddImage("Sight", L".\\Image\\Player\\black.png", 24, 24);																			break;
	case 212 : 																																					break;
	case 213 : 																																					break;

	}

	if (_count >= 400)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->Stop("Loading");
			SCENEMANAGER->ChangeScene("Stage1");
		}

		if (_count > 992)
			_count = 400;
	}
}																																							
																																							
void Loading::Render()																																		
{										
	IMAGEMANAGER->FindImage("LoadingScene")->UIRender(0, 0);
	
	if (_count >= 400)
	{
		if((_count/32)%2)
		IMAGEMANAGER->FindImage("Press")->UIRender(WINSIZEX/2,700);
		IMAGEMANAGER->FindImage("LoadingSkeletonBase")->FlipFrameRender(WINSIZEX - 60, 700, (_count / 8) % 8);
	}

	else
		IMAGEMANAGER->FindImage("LoadingSkeletonBase")->FlipFrameRender(((WINSIZEX / 400) * _count) - 60, 700, (_count / 8) % 8);

}																																							
																																							
void Loading::Release()
{

}