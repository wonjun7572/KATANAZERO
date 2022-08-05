#include "stdafx.h"
#include "BossBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ReflectEffect.h"
#include "SoundMgr.h"

float g_fBossBulletSound = 1.f;

CBossBullet::CBossBullet()
{
}


CBossBullet::~CBossBullet()
{
	Release();
}

void CBossBullet::Initialize(void)
{
	m_tInfo.fCX = 68.f;
	m_tInfo.fCY = 68.f;
	m_fSpeed = 15.f;

	m_fDiagonal = 20.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_bullet.bmp", L"BOSS_BULLET");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_bullet_reset.bmp", L"BOSS_BULLET_RESET");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_bullet_plg.bmp", L"BOSS_BULLET_PLG");
	m_pFrameKey = L"BOSS_BULLET";
	m_eRenderGroup = GAMEOBJECT;
}

int CBossBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fX > 5000.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fX < -100.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fY < -100.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fY > 1500.f)
	{
		m_bDead = true;
	}

	RotationCheck();

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD)->empty())
	{
		for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD))
		{
			if (Check_Sphere(iter, &m_tInfo))
			{
				if (!m_bEffect)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CReflectEffect>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
					CSoundMgr::Get_Instance()->PlaySound(L"reflect.wav", SOUND_MONSTER1, g_fBossBulletSound);
					m_bEffect = true;
				}
				m_bReflect = true;
			}
		}
	}

	if (!m_bReflect)
	{
		m_tInfo.fX -= cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	}
	else
	{
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY += sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	}
	float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));

	// �� ���
	m_tPoint[0].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 135.f) * (PI / 180.f)));
	m_tPoint[0].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 135.f) * (PI / 180.f)));

	// �� ���
	m_tPoint[1].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 45.f) * (PI / 180.f)));
	m_tPoint[1].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 45.f) * (PI / 180.f)));

	// �� �ϴ�						
	m_tPoint[2].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 225.f) * (PI / 180.f)));
	m_tPoint[2].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 225.f) * (PI / 180.f)));

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossBullet::Late_Update(void)
{
}

void CBossBullet::Render(HDC hDC)
{
	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	HDC hRotaionDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSS_BULLET_PLG");
	HDC hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSS_BULLET_RESET");
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSS_BULLET");

	PlgBlt(hRotaionDC, // ȸ�� ��ų �̹����� ��� �׸� ���ΰ�
		m_tPoint,	// �׸��� �׸� �簢���� ��ǥ  POINT ���� 3��, �迭�� ������ �� ���, �� ���, �� �ϴ� ��
		hMemDC,		// ��� �ִ� �̹����� �׸� ���ΰ�
		0,			// �׸� �̹��� X,Y ��ǥ
		0,
		(int)m_tInfo.fCX, // �̹��� ����, ���� ������
		(int)m_tInfo.fCY,
		NULL,
		NULL,
		NULL);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,				// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hRotaionDC,												// ��Ʈ���� ������ �ִ� dc	
		0,
		0,
		(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	BitBlt(hRotaionDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0,
		0,
		SRCCOPY);
}

void CBossBullet::Release(void)
{
}

void CBossBullet::RotationCheck()
{
	if (m_fAngle >= -10 && m_fAngle <= 0)
		m_fRotAngle = 0.f;
	else if (m_fAngle >= -20 && m_fAngle <= -10)
		m_fRotAngle = 10.f;
	else if (m_fAngle >= -30 && m_fAngle <= -20)
		m_fRotAngle = 20.f;
	else if (m_fAngle >= -40 && m_fAngle <= -30)
		m_fRotAngle = 30.f;
	else if (m_fAngle >= -50 && m_fAngle <= -40)
		m_fRotAngle = 40.f;
	else if (m_fAngle >= -60 && m_fAngle <= -50)
		m_fRotAngle = 50.f;
	else if (m_fAngle >= -70 && m_fAngle <= -60)
		m_fRotAngle = 60.f;
	else if (m_fAngle >= -80 && m_fAngle <= -70)
		m_fRotAngle = 70.f;
	else if (m_fAngle >= -90 && m_fAngle <= -80)
		m_fRotAngle = 80.f;
	else if (m_fAngle >= 180 && m_fAngle < 190)
		m_fRotAngle = 0.f;
	else if (m_fAngle >= 190 && m_fAngle < 200)
		m_fRotAngle = -10.f;
	else if (m_fAngle >= 200 && m_fAngle < 210)
		m_fRotAngle = -20.f;
	else if (m_fAngle >= 210 && m_fAngle < 220)
		m_fRotAngle = -30.f;
	else if (m_fAngle >= 220 && m_fAngle < 230)
		m_fRotAngle = -40.f;
	else if (m_fAngle >= 230 && m_fAngle < 240)
		m_fRotAngle = -50.f;
	else if (m_fAngle >= 240 && m_fAngle < 250)
		m_fRotAngle = -60.f;
	else if (m_fAngle >= 250 && m_fAngle < 260)
		m_fRotAngle = -70.f;
	else if (m_fAngle >= 260 && m_fAngle < 270)
		m_fRotAngle = -80.f;
}

bool CBossBullet::Check_Sphere(CObj* pDest, INFO* pSour)
{
	// c^2 = a^2 + b^2

	// fabs : ���밪�� �����ִ� �Լ�
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->fY);

	// sqrtf : ��Ʈ�� ���� ���� �����ִ� �Լ�
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}