#include "pch.h"
#include "CTextUI.h"

#include "CTimeMgr.h"
#include "CEngine.h"

CTextUI::CTextUI():
	m_fShowTime(1.f),
	m_fHideTime(0.f),
	m_Color{255, 255, 255}
{
	auto hFont = CreateFont(18, 0, 0, 0, 700, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Anton"));
	auto oldFont = (HFONT)SelectObject(CEngine::GetInst()->GetMainDC(), hFont);
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
		SetTextColor(_dc, RGB(m_Color.r, m_Color.g, m_Color.b));

		SetTextAlign(_dc, TA_LEFT);
		TextOut(_dc, vPos.x, vPos.y, m_Text.c_str(), m_Text.length());
	}
}

void CTextUI::finaltick(float _dt)
{
	Super::finaltick(_dt);

	m_AccTime += DT;
	
	// 보여지는 중
	if (GetAlpha() == 255 && m_fHideTime != 0 && m_fShowTime <= m_AccTime) {
		SetAlpha(0);
		m_AccTime = 0;
	}
	else if (GetAlpha() == 0 && m_fShowTime!=0 &&  m_fHideTime <= m_AccTime) {
		SetAlpha(255);
		m_AccTime = 0;
	}
}

void CTextUI::LBtnClicked(Vec2 _vMousePos)
{
	if (nullptr != m_CallBackFunc) {
		m_CallBackFunc();
	}
}
