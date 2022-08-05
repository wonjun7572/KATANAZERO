#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
	CObjMgr(const CObjMgr& rhs)				= delete;	// default 복사 생성자
	CObjMgr& operator=(const CObjMgr& rhs)  = delete;	// default 대입 연산자


public:
	// 아이디를 통하여 오브젝트를 추가한다.
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	// 아이디를 통하여 오브젝트를 삭제한다.
	void		Delete_OBJID(OBJID eID);

public:
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }

	// 아이디를 통하여 리스트를 가져온다.
	list<CObj*>*	Get_ObjList(OBJID eID) { return &m_ObjList[eID]; }
	
	// 아이디를 통하여 타겟을 가져온다.
	CObj*			Get_Target(OBJID eID, CObj* pObj);


public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*		m_pInstance;

	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderSort[RENDER_END];
	list<INFO>		m_tInfoList;
};

