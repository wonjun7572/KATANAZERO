#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
	CObjMgr(const CObjMgr& rhs)				= delete;	// default ���� ������
	CObjMgr& operator=(const CObjMgr& rhs)  = delete;	// default ���� ������


public:
	// ���̵� ���Ͽ� ������Ʈ�� �߰��Ѵ�.
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	// ���̵� ���Ͽ� ������Ʈ�� �����Ѵ�.
	void		Delete_OBJID(OBJID eID);

public:
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }

	// ���̵� ���Ͽ� ����Ʈ�� �����´�.
	list<CObj*>*	Get_ObjList(OBJID eID) { return &m_ObjList[eID]; }
	
	// ���̵� ���Ͽ� Ÿ���� �����´�.
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

