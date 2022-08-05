#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr*	CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImageKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())
	{
		CBitMap*		pBmp = new CBitMap;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImageKey, pBmp });
	}
}
HDC CBmpMgr::Find_Img(const TCHAR* pImageKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
