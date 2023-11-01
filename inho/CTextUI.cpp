#include "pch.h"
#include "CTextUI.h"

CTextUI::CTextUI()
{
}

CTextUI::CTextUI(const CTextUI& _Origin)
{
}

CTextUI::~CTextUI()
{
}

void CTextUI::render(HDC _dc)
{
	Vec2 vPos = GetRenderPos();
	SetBkMode(_dc, 1);
	SetTextColor(_dc, RGB(255, 255, 255));
	HFONT hFont, oldFont;
	hFont = CreateFont(14, 0, 0, 0, 700, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Anton"));
	oldFont = (HFONT)SelectObject(_dc, hFont);
	SetTextAlign(_dc, TA_CENTER);
	TextOut(_dc, vPos.x, vPos.y, m_Text.c_str(), m_Text.length());
}
