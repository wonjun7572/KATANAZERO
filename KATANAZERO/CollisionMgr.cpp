#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "DamageEffect.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Bullet.h"
#include "Player.h"
#include "ReflectEffect.h"
#include "BottleWreck.h"
#include "SmokeGas.h"
#include "Door.h"
#include "Monster_1.h"
#include "Monster_2.h"
#include "Monster_3.h"
#include "Smoke.h"
#include "BossBullet.h"

DWORD dwOldTime = GetTickCount();

float	g_fPlaySound2 = 1.f;

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Kill_Obj();
				Sour->Kill_Obj();
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Sour->Get_Dead() == false)
						Dest->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Sour->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"death_sword1.wav", SOUND_MONSTER1, g_fPlaySound2);
						CSoundMgr::Get_Instance()->PlaySound(L"bloodsplat1.wav", SOUND_MONSTER2, g_fPlaySound2);
						if (dwOldTime + 100 < GetTickCount())
						{
							CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CDamageEffect>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY + 10.f));
							dwOldTime = GetTickCount();
						}
					}
					Sour->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_ENEMY))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Sour->Get_Dir() == DIR_RIGHT)
					{
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET_PLAYER, CAbstractFactory<CBullet>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, DIR_LEFT));
						CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CReflectEffect>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, DIR_LEFT));
						CSoundMgr::Get_Instance()->PlaySound(L"reflect.wav", SOUND_REFLECT, g_fPlaySound2);
					}
					else if (Sour->Get_Dir() == DIR_LEFT)
					{
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET_PLAYER, CAbstractFactory<CBullet>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, DIR_RIGHT));
						CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CReflectEffect>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, DIR_RIGHT));
						CSoundMgr::Get_Instance()->PlaySound(L"reflect.wav", SOUND_REFLECT, g_fPlaySound2);
					}
					Sour->Kill_Obj();
					Dest->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_PLAYER))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"death_bullet.wav", SOUND_MONSTER1, g_fPlaySound2);
						CSoundMgr::Get_Instance()->PlaySound(L"bloodsplat1.wav", SOUND_MONSTER2, g_fPlaySound2);
						Sour->Kill_Obj();
					}
					Dest->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_KNIFE))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"knife.wav", SOUND_MONSTER1, g_fPlaySound2);
						CSoundMgr::Get_Instance()->PlaySound(L"bloodsplat4.wav", SOUND_MONSTER2, g_fPlaySound2);
						CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CDamageEffect>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY + 10.f));
						Sour->Kill_Obj();
					}
					Dest->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOTTLE))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"bottle.wav", SOUND_MONSTER1, g_fPlaySound2);
						CSoundMgr::Get_Instance()->PlaySound(L"bloodsplat2.wav", SOUND_MONSTER2, g_fPlaySound2);
						CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CDamageEffect>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY + 10.f));
						Sour->Kill_Obj();
					}
					Dest->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_WALL) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOTTLE))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					CSoundMgr::Get_Instance()->PlaySound(L"death_bottle.wav", SOUND_MONSTER1, g_fPlaySound2);
					for (int i = 0; i < 10; ++i)
					{
						CObjMgr::Get_Instance()->Add_Object(OBJ_BOTTLE_WRECK, CAbstractFactory<CBottleWreck>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY));
					}
					Sour->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SMOKE))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"explosion2.wav", SOUND_MONSTER1, g_fPlaySound2);
						Sour->Kill_Obj();
					}

					if (dynamic_cast<CSmoke*>(Sour)->Get_Damage() == true)
					{
						Dest->Kill_Obj();
					}
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_WALL) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SMOKE))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"explosion2.wav", SOUND_MONSTER1, g_fPlaySound2);
						Sour->Kill_Obj();
					}
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						if (Sour->Get_Dead() == false)
						{
							CSoundMgr::Get_Instance()->PlaySound(L"doorbreak.wav", SOUND_MONSTER1, g_fPlaySound2);
						}
						Sour->Kill_Obj();
					}
				}
			}
		}
	}
	else if ((_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_KNIFE) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)) || (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOTTLE) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (dynamic_cast<CDoor*>(Sour)->Get_Dooropen() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"doorbreak.wav", SOUND_MONSTER1, g_fPlaySound2);
						CSoundMgr::Get_Instance()->PlaySound(L"death_bottle.wav", SOUND_MONSTER1, g_fPlaySound2);
						Dest->Kill_Obj();
						Sour->Kill_Obj();
					}
					else
					{
						Sour->Kill_Obj();
					}
				}
			}
		}
	}
	else if ((_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SMOKE) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (dynamic_cast<CDoor*>(Sour)->Get_Dooropen() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"doorbreak.wav", SOUND_MONSTER1, g_fPlaySound2);
						CSoundMgr::Get_Instance()->PlaySound(L"explosion2.wav", SOUND_MONSTER1, g_fPlaySound2);
						Dest->Kill_Obj();
						Sour->Kill_Obj();
					}
					else
					{
						Sour->Kill_Obj();
					}
				}
			}
		}
	}
	else if ((_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_PLAYER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (dynamic_cast<CDoor*>(Sour)->Get_Dooropen() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"doorbreak.wav", SOUND_MONSTER1, g_fPlaySound2);
						Dest->Kill_Obj();
						Sour->Kill_Obj();
					}
					else
					{
						Sour->Kill_Obj();
					}
				}
			}
		}
	}
	else if ((_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_ENEMY) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (dynamic_cast<CDoor*>(Sour)->Get_Dooropen() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"doorbreak.wav", SOUND_MONSTER1, g_fPlaySound2);
						Dest->Kill_Obj();
						Sour->Kill_Obj();
					}
					else
					{
						Sour->Kill_Obj();
					}
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_KNIFE) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_ENEMY) || (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOTTLE) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_ENEMY)))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Sour->Get_Dead() == false)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"reflect.wav", SOUND_MONSTER1, g_fPlaySound2);
						if (dwOldTime + 100 < GetTickCount())
						{
							CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CReflectEffect>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, DIR_LEFT));
							dwOldTime = GetTickCount();
						}
					}
					Dest->Kill_Obj();
					Sour->Kill_Obj();
				}
			}
		}
	}
	else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SMOKE) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET_ENEMY))
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					if (Dest->Get_Dead() == false)
					{
						if (dwOldTime + 100 < GetTickCount())
						{
							CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CReflectEffect>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, DIR_LEFT));
							dwOldTime = GetTickCount();
						}
						CSoundMgr::Get_Instance()->PlaySound(L"explosion3.wav", SOUND_MONSTER1, g_fPlaySound2);
						Sour->Kill_Obj();
					}
					Dest->Kill_Obj();
				}
			}
		}
	}
	else
	{
		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Check_Sphere(Dest, Sour))
				{
					Dest->Kill_Obj();
					Sour->Kill_Obj();
				}
			}
		}
	}
}
//   충돌하는 대상			장애물
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float		fX = 0.f, fY = 0.f;
			if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_WALL))
			{
				if (Check_Rect(Dest, Sour, &fX, &fY))
				{
					// 상.하 충돌
					if (fX > fY)
					{
						// 하 충돌
						if (Dest->Get_Info().fY > Sour->Get_Info().fY)
							Dest->Set_PosY(fY);
						// 상 충돌
						else
							Dest->Set_PosY(-fY);
					}
					// 좌.우 충돌
					else
					{
						dynamic_cast<CPlayer*>(Dest)->Set_EnvState(WALL);
						// 우 충돌
						if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						{
							dynamic_cast<CPlayer*>(Dest)->Set_LookDir(LOOK_LEFT);
						}

						// 좌 충돌
						else
						{
							dynamic_cast<CPlayer*>(Dest)->Set_LookDir(LOOK_RIGHT);
						}
					}
				}
			}

			else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR))
			{
				if (Check_Rect(Dest, Sour, &fX, &fY) && dynamic_cast<CDoor*>(Sour)->Get_Dooropen() == false)
				{
					// 우 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						dynamic_cast<CPlayer*>(Dest)->Set_LookDir(LOOK_LEFT);
						Dest->Set_PosX(fX);
					}

					// 좌 충돌
					else
					{
						dynamic_cast<CPlayer*>(Dest)->Set_LookDir(LOOK_RIGHT);
						Dest->Set_PosX(-fX);
					}
				}
			}
			else if (_Dest == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER) && _Sour == *CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR))
			{
				if (Check_Rect(Dest, Sour, &fX, &fY) && dynamic_cast<CDoor*>(Sour)->Get_Dooropen() == false)
				{
					// 우 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						Dest->Set_PosX(fX);
					}

					// 좌 충돌
					else
					{
						Dest->Set_PosX(-fX);
					}
				}
			}
			else if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// 상.하 충돌
				if (fX > fY)
				{
					// 하 충돌
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
						Dest->Set_PosY(fY);

					// 상 충돌
					else
						Dest->Set_PosY(-fY);
				}

				// 좌.우 충돌
				else
				{
					// 우 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						Dest->Set_PosX(fX);

					// 좌 충돌
					else
						Dest->Set_PosX(-fX);
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fWidth < fRadiusX) && (fHeight < fRadiusY))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}


	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	// c^2 = a^2 + b^2

	// fabs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrtf : 루트를 씌워 값을 구해주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}
