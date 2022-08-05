#pragma once

#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;
}INFO;

typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint(void) { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{

	}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLeftPt;
	LINEPOINT		tRightPt;

	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLeftPt, LINEPOINT& _tRightPt)
		: tLeftPt(_tLeftPt), tRightPt(_tRightPt)
	{

	}


}LINE;

typedef	struct	tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;
}FRAME;