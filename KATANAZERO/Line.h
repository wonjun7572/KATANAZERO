#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& tLeftPt, LINEPOINT& tRightPt);
	CLine(LINE& rLine);
	~CLine();

public:
	const LINE& Get_LineInfo(void) const { return m_tInfo; }

	void	Render(HDC hDC);

private:
	LINE			m_tInfo;
};

