#include "pch.h"
#include "CBackground.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"
#include "CLogMgr.h"

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

void CBackground::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();

	if (nullptr == m_Tex) {
		Rectangle(_dc,
			(int)vRenderPos.x,
			(int)vRenderPos.y,
			(int)(vRenderPos.x + TILE_SIZE),
			(int)(vRenderPos.y + TILE_SIZE));
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

	}
}

void CBackground::tick(float _dt)
{	
}

