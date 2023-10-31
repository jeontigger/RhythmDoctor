#include "pch.h"

#include "CMonster.h"

#include "CPaletteMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CProjectile.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"

CMonster::CMonster() : 
    m_Info{}, 
    m_Collider(nullptr), 
    m_AI(nullptr),
    m_Texture(nullptr)
{
    m_Collider = AddComponent<CCollider>(L"MonsterCollider");

    m_Info.HP = 5.f;
    m_Texture = CAssetMgr::GetInst()->LoadTexture(L"StartTex", L"texture\\MagicCircle_01.png");

    m_AI = AddComponent<CStateMachine>(L"AI");
    m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CNormalMonIdle);
    m_AI->AddState((UINT)ENORMAL_MON_STATE::TRACE, new CNormalMonTrace);
}

CMonster::CMonster(const CMonster& _Origin):
    CObj(_Origin),
    m_Info(_Origin.m_Info),
    m_Collider(nullptr),
    m_Texture(_Origin.m_Texture)
{
    m_Collider = GetComponent<CCollider>();
}

CMonster::~CMonster() {}

void CMonster::begin()
{
    m_Collider->SetScale(GetScale() - 10.f);


    Vec2 vPos = GetPos();
    m_AI->AddDataToBlackboard(L"Initial Position", vPos);
    m_AI->AddDataToBlackboard(L"Detect Range", 500.f);
    m_AI->AddDataToBlackboard(L"Attack Range", 50.f);
    m_AI->AddDataToBlackboard(L"Speed", 100.f);


    m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CMonster::tick(float _DT) {
    Super::tick(_DT);

    /*Vec2 vPos = GetPos();

    

    static float ftime = 0;
    static bool  flag = false;
    ftime += CTimeMgr::GetInst()->GetDeltaTime();
    

    SetPos(vPos);*/
}

void CMonster::render(HDC _dc) {
    Vec2 vRenderPos = GetRenderPos();
    Vec2 vScale = GetScale();

    if (m_Texture == nullptr) {
        CPaletteMgr* palette = CPaletteMgr::GetInst();

        palette->SelectPen(CPaletteMgr::PenColor::PRED);
        palette->SelectBrush(CPaletteMgr::BrushColor::BRED);
        Ellipse(_dc, int(vRenderPos.x - vScale.x / 2), int(vRenderPos.y - vScale.y / 2),
            int(vRenderPos.x + vScale.x / 2), int(vRenderPos.y + vScale.y / 2));

    }
    else {
        BLENDFUNCTION blend = {};
        blend.BlendOp = AC_SRC_OVER;
        blend.BlendFlags = 0;

        blend.SourceConstantAlpha = 255; // 0 ~ 255
        blend.AlphaFormat = AC_SRC_ALPHA; // 0

        AlphaBlend(_dc
            , int(vRenderPos.x - m_Texture->GetWidth() / 2.f)
            , int(vRenderPos.y - m_Texture->GetHeight() / 2.f)
            , m_Texture->GetWidth()
            , m_Texture->GetHeight()
            , m_Texture->GetDC()
            , 0, 0
            , m_Texture->GetWidth()
            , m_Texture->GetHeight()
            , blend);

    }
    Super::render(_dc);
}

void CMonster::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if (dynamic_cast<CProjectile*>(_OtherObj)) {
        m_Info.HP -= 1.f;
        if (m_Info.HP <= 0.f) {
            Destroy();
        }
    }

    
}
