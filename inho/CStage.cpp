#include "pch.h"
#include "CStage.h"

#include "CPaletteMgr.h"
#include "CLogMgr.h"
#include "CKeyMgr.h"
#include "CEngine.h"

#include "CTextUI.h"

CStage::CStage() :
    m_strLevel(L"X-X"),
    m_strName(L"XXXXXX"),
    m_strRank(L""),
    m_Rank(Stage_Rank::END),
    m_iDifficulty(0),
    m_strDescription(L"xxxxxxX"),
    m_bIsBoss(true),
    m_fStrOffset(100.f),
    m_fStrDiff(23.f)
{
    SetRank(Stage_Rank::A);
    AddComponent<CAnimator>();

}

CStage::~CStage()
{
}

void CStage::tick(float _dt)
{
    Super::tick(_dt);
}

void CStage::render(HDC _dc)
{
    Super::render(_dc);
    Vec2 vRenderPos = GetRenderPos();
    Vec2 m_vScale = GetScale();

    // 텍스트 위치가 필요함
    // 아래에서부터 위로 쌓는 식이면 될 듯
    // 아래에서부터 얼만큼 떨어져 있는지 , 그 후로 얼만큼씩 떨어지는지
    Vec2 vPos = GetRenderPos();
    SetBkMode(_dc, 1);
    SetTextColor(_dc, RGB(0,0,0));

    SetTextAlign(_dc, TA_CENTER);
    
    if (m_bIsBoss) {
        SetTextColor(_dc, RGB(0xD7, 0x4A, 0x8D));
        TextOut(_dc, vPos.x, vPos.y - m_fStrOffset - m_fStrDiff * 3, L"보스", 2);
    }
    SetTextColor(_dc, RGB(0xCC, 0xFF, 0x22));
    TextOut(_dc, vPos.x, vPos.y - m_fStrOffset - m_fStrDiff * 2, m_strLevel.c_str(), m_strLevel.length());
    SetTextColor(_dc, RGB(0x6A, 0xF2, 0xF0));
    TextOut(_dc, vPos.x, vPos.y - m_fStrOffset - m_fStrDiff * 1, m_strName.c_str(), m_strName.length());
    SetTextColor(_dc, RGB(0xff, 0xff, 0xff));
    TextOut(_dc, vPos.x, vPos.y - m_fStrOffset - m_fStrDiff * 0, m_strRank.c_str(), m_strRank.length());

    // 디버깅용 초록 네모 상자 출력
    {
        if (!DEBUG_RENDER)
            return;
        CPaletteMgr::GetInst()->SelectPen(CPaletteMgr::PenColor::PGREEN);
        CPaletteMgr::GetInst()->SelectBrush(CPaletteMgr::BrushColor::BHOLLOW);

        Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f),
            int(vRenderPos.y - m_vScale.y / 2.f),
            int(vRenderPos.x + m_vScale.x / 2.f),
            int(vRenderPos.y + m_vScale.y / 2.f));
    }
}

void CStage::SetRank(Stage_Rank _rank)
{
    m_strRank = L"랭크: A";
}
