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
	if (GetAlpha() == 255) {
		Vec2 vPos = GetRenderPos();
		SetBkMode(_dc, 1);
		SetTextColor(_dc, RGB(255, 255, 255));

		SetTextAlign(_dc, TA_CENTER);
		TextOut(_dc, vPos.x, vPos.y, m_Text.c_str(), m_Text.length());
	}
}
