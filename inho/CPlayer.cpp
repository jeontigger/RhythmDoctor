#include "pch.h"

#include "CPlayer.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CPaletteMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CGuidedProjectile.h"
#include "CProjectile.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"

#include "CLogMgr.h"
#include "CPlatform.h"

#include "components.h"

CPlayer::CPlayer() :
    m_Collider(nullptr),
    m_Animator(nullptr),
    m_Movement(nullptr)
{
    SetName(L"Player");
    // 컴포넌트 추가
    m_Collider = AddComponent<CCollider>(L"PlayerCollider");
    m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
    m_Collider->SetScale(Vec2(40.f, 80.f));
    m_Collider->SetOffsetPos(Vec2(0.f, -40.f));

    CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\link.bmp");
    m_Animator = AddComponent<CAnimator>(L"Animator");
    Vec2 offset(0.f, -60.f);
    /*m_Animator->CreateAnimation(L"WalkDown", pAtlas, Vec2(0.f, 520.f), Vec2(120, 130), offset, 0.05f, 10);
    m_Animator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), offset, 0.05f, 10);
    m_Animator->CreateAnimation(L"WalkUp", pAtlas, Vec2(0.f, 780.f), Vec2(120, 130), offset, 0.05f, 10);
    m_Animator->CreateAnimation(L"WalkRight", pAtlas, Vec2(0.f, 910.f), Vec2(120, 130), offset, 0.05f, 10);

    m_Animator->CreateAnimation(L"IdleDown", pAtlas, Vec2(0.f, 0.f), Vec2(120, 130), offset, 0.05f, 3);
    m_Animator->CreateAnimation(L"IdleLeft", pAtlas, Vec2(0.f, 130.f), Vec2(120, 130), offset, 0.05f, 3);
    m_Animator->CreateAnimation(L"IdleUp", pAtlas, Vec2(0.f, 260.f), Vec2(120, 130), offset, 0.05f, 1);
    m_Animator->CreateAnimation(L"IdleRight", pAtlas, Vec2(0.f, 390.f), Vec2(120, 130), offset, 0.05f, 3);

    m_Animator->SaveAnimation(L"animdata");*/


    m_Movement = AddComponent<CMovement>(L"PlayerMovement");
    m_Movement->SetMass(1.f);
    m_Movement->SetInitSpeed(200.f);
    m_Movement->SetMaxSpeed(400.f);
    m_Movement->UseGravity(false);
    m_Movement->SetGravity(Vec2(0.f, 980.f));
    m_Movement->SetFrictionScale(1000.f);
    m_Movement->SetGround(true);

}

CPlayer::CPlayer(const CPlayer& _Origin):
    CObj(_Origin),
    m_Collider(nullptr),
    m_Animator(nullptr),
    m_Movement(nullptr)
{
    m_Collider = GetComponent<CCollider>();
    m_Animator = GetComponent<CAnimator>();
    m_Movement = GetComponent<CMovement>();
}

CPlayer::~CPlayer() {
    
}

void CPlayer::tick(float _DT) {
    Super::tick(_DT);

    Vec2 vPos = GetPos();

    if (KEY_PRESSED(A))
    {
        m_Movement->AddForce(Vec2(-300.f, 0.f));
        m_Animator->Play(L"WalkLeft", true);
    }

    if (KEY_RELEASED(A))
    {
        m_Animator->Play(L"IdleLeft", true);
    }

    if (KEY_PRESSED(D))
    {
        m_Movement->AddForce(Vec2(300.f, 0.f));
        m_Animator->Play(L"WalkRight", true);
    }
    if (KEY_RELEASED(D))
    {
        m_Animator->Play(L"IdleRight", true);
    }


    if (KEY_PRESSED(W))
    {
        m_Movement->AddForce(Vec2(0.f, -300.f));
        m_Animator->Play(L"WalkUp", true);
    }
    if (KEY_RELEASED(W))
    {
        m_Animator->Play(L"IdleUp", true);
    }

    if (KEY_PRESSED(S))
    {
        m_Movement->AddForce(Vec2(0.f, 300.f));
        m_Animator->Play(L"WalkDown", true);
    }
    if (KEY_RELEASED(S))
    {
        m_Animator->Play(L"IdleDown", true);
    }

    if (KEY_TAP(SPACE)) {
        m_Movement->SetGround(false);
        m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -500.f));
    }

    if (KEY_TAP(F)) {
        CCamera::GetInst()->FadeIn(2.5f);
    }
    if (KEY_TAP(G)) {
        CCamera::GetInst()->FadeOut(2.5f);
    }


    SetPos(vPos);
}


void CPlayer::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if (dynamic_cast<CPlatform*>(_OtherObj)) {
        m_Movement->SetGround(true);
    }
}

void CPlayer::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if (dynamic_cast<CPlatform*>(_OtherObj)) {
        m_Movement->SetGround(false);
    }
}
