#include "pch.h"
#include "CPlayLevel.h"

#include "CPlayer.h"
#include "CPlatform.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"

void CPlayLevel::init()
{

    CPlayer* pPlayer = new CPlayer;

    pPlayer->SetPos(Vec2(500.f, 200.f));
    pPlayer->SetScale(Vec2(50.f, 50.f));

    AddObject(PLAYER, pPlayer);

    CMonster* pMonster = nullptr;

    pMonster = new CMonster;
    pMonster->SetPos(Vec2(900.f, 500.f));
    pMonster->SetScale(Vec2(100.f, 100.f));
    AddObject(MONSTER, pMonster);


    CPlatform* pPlatform = new CPlatform;
    pPlatform->SetPos(Vec2(800.f, 700.f));
    AddObject(PLATFORM, pPlatform);

    // 카메라 설정
    Vec2 vLookAt = CEngine::GetInst()->GetResolution();
    vLookAt /= 2.f;
    CCamera::GetInst()->SetLookAt(vLookAt);


    CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
    CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER_PJ);
    CCollisionMgr::GetInst()->CheckCollision(PLATFORM, PLAYER);
}

void CPlayLevel::enter()
{

    CCamera::GetInst()->FadeOut(1.0f);
    CCamera::GetInst()->FadeIn(1.0f);

    /*CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
    pSound->SetVolume(100);
    pSound->SetPosition(45.f);
    pSound->Play(true);*/
}

void CPlayLevel::exit()
{
    DeleteAllObjects();
}

void CPlayLevel::tick()
{
    CLevel::tick();

    if (KEY_TAP(KEY::ENTER)) {
        ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
    }

    if (KEY_TAP(KEY::M))
    {
        /*CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\BGM_Stage1.wav");
        pSound->SetVolume(100);
        pSound->SetPosition(45.f);
        pSound->Play(true);*/
    }
}
