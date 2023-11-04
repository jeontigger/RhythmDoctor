#include "pch.h"
#include "CStageSelectLevel.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"


//
#include "CBackground.h"
#include "CStage.h"
//
void CStageSelectLevel::init()
{
    CBackground* pBg;
    
    // 배경 생성
    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBGL", L"texture\\StageSelectLevelBG_L.png");
    pBg->SetPos({ (float)pBg->GetWidth() - 740.f, 125.f});
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBGR", L"texture\\StageSelectLevelBG_R.png");
    pBg->SetPos({ (float)pBg->GetWidth() + 37.f, 125.f });
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectLight", L"texture\\StageSelectLight.png");
    pBg->SetPos({ (float)pBg->GetWidth() - 995.f, 125.f });
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);

    



    CStage* pStage = new CStage;
    pStage->SetPos({300, 250});
    pStage->SetScale({ 40, 40 });
    pStage->SetBoss(true);
    pStage->SetLevel(L"1-1");
    pStage->SetName(L"Samurai Techno");
    pStage->SetRank(Stage_Rank::A);
  
    CAnimator* pAnimator = pStage->GetComponent<CAnimator>();
    //CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SamuraiAtlas", L"texture\\Samurai.png");
    //pAnimator->CreateAnimation(L"SamuraiIdle", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.3f, 2);
    //pAnimator->SaveAnimation(L"animdata");
    pAnimator->LoadAnimation(L"animdata\\SamuraiIdle.txt");
    pAnimator->Play(L"SamuraiIdle", true);




    //m_Animator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), offset, 0.05f, 10);
    AddObject(STAGE, pStage);
    


    // 카메라 설정
    Vec2 vLookAt = CEngine::GetInst()->GetResolution();
    vLookAt /= 2.f;
    CCamera::GetInst()->SetLookAt(vLookAt);
}

void CStageSelectLevel::enter()
{
    CCamera::GetInst()->FadeIn(1.0f);
}

void CStageSelectLevel::exit()
{
    DeleteAllObjects();
}

void CStageSelectLevel::tick()
{
    CLevel::tick();
    if (KEY_TAP(ESC)) {
        ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL);
    }

}
