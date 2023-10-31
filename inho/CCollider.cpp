#include "pch.h"

#include "CCollider.h"

#include "CCamera.h"
#include "CEngine.h"
#include "CObj.h"
#include "CPaletteMgr.h"

#include "CLayer.h"
#include "CLevel.h"
#include "CLevelMgr.h"


CCollider::CCollider(CObj* _Owner) : 
    CComponent(_Owner),
    m_iCollisionCount(0)
{}

CCollider::CCollider(const CCollider & _Origin):
    CComponent(_Origin),
    m_vOffsetPos(_Origin.m_vOffsetPos),
    m_vScale(_Origin.m_vScale),
    m_vFinalPos(_Origin.m_vFinalPos),
    m_iCollisionCount(0)
{

}


CCollider::~CCollider() {}

void CCollider::finaltick(float _DT) {
    Vec2 vOwnerPos = GetOwner()->GetPos();

    m_vFinalPos = vOwnerPos + m_vOffsetPos;

    int iLayerIdx = GetOwner()->GetLayerIdx();

    assert(!(iLayerIdx < 0));
    CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);

    pCurLayer->RegisterCollider(this);
}

void CCollider::render(HDC _dc) {
    if (!DEBUG_RENDER)
        return;

    CPaletteMgr::GetInst()->SelectPen(CPaletteMgr::PenColor::PGREEN);
    CPaletteMgr::GetInst()->SelectBrush(CPaletteMgr::BrushColor::BHOLLOW);

    Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

    if (0 < m_iCollisionCount) {
        CPaletteMgr::GetInst()->SelectPen(CPaletteMgr::PenColor::PRED);
    }
    else {
        CPaletteMgr::GetInst()->SelectPen(CPaletteMgr::PenColor::PGREEN);
    }

    // render
    Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f),
              int(vRenderPos.y - m_vScale.y / 2.f),
              int(vRenderPos.x + m_vScale.x / 2.f),
              int(vRenderPos.y + m_vScale.y / 2.f));
}

void CCollider::BeginOverlap(CCollider* _OtherCol)
{
    ++m_iCollisionCount;
    GetOwner()->BeginOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::Overlap(CCollider* _OtherCol)
{
    GetOwner()->Overlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::EndOverlap(CCollider* _OtherCol)
{
    --m_iCollisionCount;
    GetOwner()->EndOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}
