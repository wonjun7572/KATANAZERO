#pragma once

#pragma once

enum OBJID
{
	OBJ_PLAYER,
	OBJ_SHADOW,
	OBJ_BOSS,
	OBJ_MONSTER,
	OBJ_ITEM,
	OBJ_SWORD,
	OBJ_KNIFE,
	OBJ_DOOR,
	OBJ_CURTAIN,
	OBJ_BOTTLE,
	OBJ_BOTTLE_WRECK,
	OBJ_SMOKE,
	OBJ_SMOKE_GAS,
	OBJ_BULLET_PLAYER,
	OBJ_BULLET_ENEMY,
	OBJ_BULLET_BOSS,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_TRAP,
	OBJ_EXPLOSION,
	OBJ_WALL,
	OBJ_END
};

enum DIR { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_LOADING_1, SC_LOADING_2, SC_LOADING_3, SC_EDIT, SC_STAGE_1, SC_STAGE_2, SC_PRE_STAGE_BOSS, SC_STAGE_BOSS, SC_END };

enum PLAYER_LOOKAT { LOOK_RIGHT, LOOK_LEFT, LOOK_END };

enum STATE
{
	IDLE,
	WALK,
	WALK_L,
	WALK_R,
	RUN,
	RUN_L,
	RUN_R,
	JUMP,
	FALL,
	RUNTOIDLE,
	IDLETORUN,
	ROLL,
	FLIP,
	CROUCH,
	GRAB_WALL,
	ATTACK,
	ATTACK_L,
	ATTACK_R,
	HIT,
	PARRY,
	DEAD,
	MOTION_END
};

enum PLAYER_ENVIRONMENT { GROUND, GROUND_DOWN, AIR, WALL, BOSS_PATTERN, FINISH, EN_END };

enum RENDERID { BACKGROUND, HIT_EFFECT, ENEMY, GAMEOBJECT,EFFECT, UI, RENDER_END };

enum CHANNELID { SOUND_EFFECT, SOUND_REFLECT, SOUND_BGM, SOUND_PLAYER, SOUND_MONSTER1, SOUND_MONSTER2, SOUND_MONSTER3, SOUND_BOSS, SOUND_BOSS2, SOUND_PRESTAGE, SOUND_SLOW_IN , SOUND_SLOW_OUT,  MAXCHANNEL };