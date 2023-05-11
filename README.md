# KATANAZERO
《카타나 제로》는 독립 개발자 저스틴 스탠더가 개발하고 디지털 디볼버가 배급한 2019년 핵 앤드 슬래시 플랫폼 게임이다. 
macOS, 마이크로소프트 윈도우 및 닌텐도 스위치로 제작돼 2019년 4월 18일 출시됐다. 
게임 배경은 네오느와르풍의 반이상향 대도시이다. 

개발: Askiisoft

이 레포지토리는 카타나 제로를 모작하였습니다.

- 사용 엔진 : WindowAPI
- 사용 언어 : C++
- 사용 환경 : VisualStudio
- 사용 라이브러리 : FMOD(사운드)
- 영상 : https://youtu.be/BnnWSxhOGas

# 주 사용 기술

## AlphaBlending

WindowAPI로 처음 코딩을 하게되면서 가장 고민하면서 가장 쾌감을 느꼈던 알파블렌딩을 소개하겠습니다.

1. 알파처리를 그릴 DC (AlphaDC)와 처리할 이미지 정보(TempDC)를 따로 기록해줍니다.

2. 화면 DC의 정보를 AlphaDC에 복사해 줍니다.

3. m_BlendFunction에 저장되어있는 Alpha Blending의 옵션값을 초기화 시에 저장해두었고 알파 처리로 출력하고자 하는 DC의 정보를 알파 DC에 복사합니다.

4. AlphaBlend 함수를 호출하여, BackDC(매개변수로 들어오는 hDC)에 준비된 알파 DC에서 알파 처리된 부분을 복사해서 넣어줍니다.

(기존에 있는 윈도우 함수를 활용하였습니다.)

ex) 사용예시

void CShadow::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	HDC AlphaDC = CreateCompatibleDC(hMemDC);
	HBITMAP TempDC = CreateCompatibleBitmap(hMemDC, WINCX, WINCY);
	HBITMAP	OldTempDC = (HBITMAP)SelectObject(AlphaDC, TempDC);
	m_BlendFunction.SourceConstantAlpha = m_iAlpha; // 0 ~ 255
	
	if (!m_bRender)
	{ 
		GdiTransparentBlt(AlphaDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

		GdiTransparentBlt(AlphaDC, 
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY, 
			hMemDC, 
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion, 
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

		GdiAlphaBlend(hDC,
			m_tRect.left + iScrollX, 
			m_tRect.top + iScrollY, 
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY, AlphaDC, 
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY,
			m_BlendFunction);
	}
	DeleteObject(SelectObject(AlphaDC, OldTempDC));
	DeleteDC(AlphaDC);
}

# 코드 부연 설명

int iScrollX, iScroolY → 해상도에 맞춰 맵의 크기를 스크롤 하기 위한 변수입니다.

// 이를 통해 맵의 크기를 벗어나서 렌더한다고하면 Lock을 걸어 더 이상 스크롤 되지 못하게 합니다. 

TCHAR*	m_pFrameKey;    → 이미지를 찾기위한 키값입니다.

map<const TCHAR*, CBitMap*>	m_mapBit; // map 자료구조를 통해 CBitMap 주소를 가져옵니다.

HDC CBmpMgr::Find_Img(const TCHAR* pImageKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}


CTag_Finder라는 함수객체를 통하여 찾게 됩니다.

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pKey)
		: m_pKey(pKey) {}

public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		if (!lstrcmp(m_pKey, Pair.first))
			return true;

		return false;
	}

private:
	const TCHAR*		m_pKey;
};

()연산자를 오버로딩하여 함수 템플릿을 구현하였습니다.
