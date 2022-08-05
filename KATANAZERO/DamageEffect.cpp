#include "stdafx.h"
#include "DamageEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CDamageEffect::CDamageEffect()
{
}

CDamageEffect::~CDamageEffect()
{
}

void CDamageEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 1600.f, 1600.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Plg.bmp", L"Plg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect_hit_lazer.bmp", L"HIT_LAZER_EFFECT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Reset.bmp", L"Reset");
	m_pFrameKey = L"HIT_LAZER_EFFECT";
	m_fSpeed = 100.f;
	m_eRenderGroup = EFFECT;
	m_dwOldTime = GetTickCount();
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	// �� ������ �ؽ�ó �����Ǵ� ���ο� ���콺 �����Ϳ��� ����
}

int CDamageEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bGetAngle)
	{
		// tan ���� ���콺�����Ϳ��� ���� 0~180  -180~0
		m_fAngle = atan2f((dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y - m_tInfo.fY), (m_tInfo.fX - dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().x)) / (PI / 180.f);
		//m_fAngle = 45.f;
		float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));

		// �� ���
		m_tPoint[0].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fAngle + 135.f) * (PI / 180.f)));
		m_tPoint[0].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fAngle + 135.f) * (PI / 180.f)));

		// �� ���
		m_tPoint[1].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fAngle + 45.f) * (PI / 180.f)));
		m_tPoint[1].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fAngle + 45.f) * (PI / 180.f)));

		// �� �ϴ�						
		m_tPoint[2].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fAngle + 225.f) * (PI / 180.f)));
		m_tPoint[2].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fAngle + 225.f) * (PI / 180.f)));
		float fAngle = atan2f(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Info().fY - dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y, dynamic_cast<CPlayer*>(m_pPlayer)->Get_Info().fX - (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().x)) * (180.f / PI);
	
		m_tInfo.fX -= cosf(fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(fAngle * (PI / 180.f)) * m_fSpeed;
		m_bGetAngle = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CDamageEffect::Late_Update(void)
{
}

void CDamageEffect::Render(HDC hDC)
{
	HDC hRotaionDC = CBmpMgr::Get_Instance()->Find_Img(L"Plg");
	HDC hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"Reset");
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

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
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hRotaionDC,					// ��Ʈ���� ������ �ִ� dc
		0, 						// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		0,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(31, 31, 31));	// ������ �ȼ��� ����

	BitBlt(hRotaionDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0,
		0,
		SRCCOPY);

	if (m_dwOldTime + 200 < GetTickCount())
	{
		m_bDead = true;

		m_dwOldTime = GetTickCount();
	}
}

void CDamageEffect::Release(void)
{
}
