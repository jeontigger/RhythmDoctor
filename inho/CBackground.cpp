#include "pch.h"
#include "CBackground.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"
#include "CLogMgr.h"
#include "CEngine.h"
#include "CPaletteMgr.h"

CBackground::CBackground():
	m_Tex(nullptr)
{
}

CBackground::~CBackground()
{
}

void CBackground::SetTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	m_Tex = CAssetMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
}

void CBackground::SetTexture(CTexture* _tex)
{
	m_Tex = _tex;
}

void CBackground::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();

	if (nullptr == m_Tex) {
		Rectangle(_dc,
			(int)vRenderPos.x,
			(int)vRenderPos.y,
			(int)(vRenderPos.x)+10,
			(int)(vRenderPos.y)+10);
	}
	else {
		UINT width = m_Tex->GetWidth();
		UINT heigth = m_Tex->GetHeight();
	

		BLENDFUNCTION blend = {};
        blend.BlendOp = AC_SRC_OVER;
        blend.BlendFlags = 0;

        blend.SourceConstantAlpha = GetAlpha(); // 0 ~ 255
        blend.AlphaFormat = AC_SRC_ALPHA; // 0

        AlphaBlend(_dc
            , int(vRenderPos.x - width / 2.f)
            , int(vRenderPos.y - heigth / 2.f)
            , width* GetScale().x
            , heigth * GetScale().y
            , m_Tex->GetDC()
            , 0, 0
            , width
            , heigth
            , blend);
        // 디버깅용 초록 네모 상자 출력
        {
            if (!DEBUG_RENDER)
                return;
            CPaletteMgr::GetInst()->SelectPen(CPaletteMgr::PenColor::PGREEN);
            CPaletteMgr::GetInst()->SelectBrush(CPaletteMgr::BrushColor::BHOLLOW);
            

            Rectangle(_dc, int(vRenderPos.x - m_Tex->GetWidth() / 2.f),
                int(vRenderPos.y - m_Tex->GetHeight() / 2.f),
                int(vRenderPos.x + m_Tex->GetWidth() / 2.f),
                int(vRenderPos.y + m_Tex->GetHeight() / 2.f));
        }
	}
}

void CBackground::tick(float _dt)
{	
}

