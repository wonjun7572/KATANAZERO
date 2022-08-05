#pragma once

#include "Obj.h"
#include "Shadow.h"
#include "Door.h"

template <typename T>
class CAbstractFactory
{
public:
	// 생성
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	// 그림자 생성
	static CObj*		Create_Shadow(DWORD _plusTime , int _alpha )
	{
		CObj*		pObj = new T;

		pObj->Initialize();
		dynamic_cast<CShadow*>(pObj)->SetTime(_plusTime);
		dynamic_cast<CShadow*>(pObj)->SetAlpha(_alpha);

		return pObj;
	}

	// 생성
	static CObj*		Create_size(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Size(_fCX, _fCY);
		return pObj;
	}

	static CObj*		Create_Gas(float _fX, float _fY , int _iAlpha)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Alpha(_iAlpha);
		return pObj;
	}

	// 포지션과 엥글값을 넣어줄 수 있음
	static CObj*		Create(float _fX, float _fY, DIR _eDir = DIR_END, float _fAngle = 0.f)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Dir(_eDir);
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		return pObj;
	}

public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};

