#include "pch.h"
#include "CStageSelectLevel.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"


//
#include "CBackground.h"
#include "CStage.h"
#include "CAnimUI.h"

//
CStageSelectLevel::CStageSelectLevel():
    m_cursorIdx(0),
    m_Veil(nullptr)
{
    
}

CStageSelectLevel::~CStageSelectLevel()
{
}

void CStageSelectLevel::init()
{
    CBackground* pBg;
    float veilWidth = 0;
    // 배경 생성
    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBGL", L"texture\\StageSelectLevelBG_L.png");
    pBg->SetPos({ (float)pBg->GetWidth() - 740.f, 125.f});
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);
    veilWidth += pBg->GetWidth();

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBGR", L"texture\\StageSelectLevelBG_R.png");
    pBg->SetPos({ (float)pBg->GetWidth() + 37.f, 125.f });
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);
    veilWidth += pBg->GetWidth();

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectLight", L"texture\\StageSelectLight.png");
    pBg->SetPos({ (float)pBg->GetWidth() - 995.f, 125.f });
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);

    m_Veil = new CBackground;
    m_Veil->SetTexture(L"StageVeil", L"texture\\blackPixel.png");
    m_Veil->SetPos({ -1000.f, 0.f});
    m_Veil->SetScale({ veilWidth,200.f });
    m_Veil->SetAlpha(0);
    AddObject(BACKGROUND, m_Veil);

    // 사무라이
    CStage* pStage = new CStage;
    pStage->SetPos({300, Stage_YPosValue });
    pStage->SetScale({ 40, 40 });
    pStage->SetBoss(true);
    pStage->SetLevel(L"1-1");
    pStage->SetName(L"Samurai Techno");
    pStage->SetRank(Stage_Rank::A);
    pStage->SetCameraOffset({ 100.f,0.f });
  
    CAnimator* pAnimator = pStage->GetComponent<CAnimator>();
    //CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SamuraiAtlas", L"texture\\Samurai.png");
    //pAnimator->CreateAnimation(L"SamuraiIdle", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.3f, 2);
    //pAnimator->SaveAnimation(L"animdata");
    pAnimator->LoadAnimation(L"animdata\\SamuraiIdle.txt");
    pAnimator->Play(L"SamuraiIdle", true);

    AddObject(STAGE, pStage);
    m_vecStages.push_back(pStage);

    // 인섬니악 생성
    pStage = new CStage;
    pStage->SetPos({ 400, Stage_YPosValue });
    pStage->SetScale({ 42, 42 });
    pStage->SetBoss(true);
    pStage->SetLevel(L"1-XN");
    pStage->SetName(L"Insomniac");
    pStage->SetRank(Stage_Rank::UNCOMPLETED);
    pStage->SetCameraOffset({ 100.f,0.f });
    pStage->SetIsLeft(false);

    pAnimator = pStage->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\InsomniacIdle.txt");
    pAnimator->Play(L"InsomniacIdle", true);

    AddObject(STAGE, pStage);
    m_vecStages.push_back(pStage);

    // 스테이지 커서 생성
    m_StageArrow = new CAnimUI;
    m_StageArrow->SetPos(m_vecStages[0]->GetPos());

    // 스테이지 커서 위 화살표
    CAnimUI* arrow = new CAnimUI;
    arrow->SetScale({ 3, 5 });
    arrow->SetPos({ 0, -50 });
    pAnimator = arrow->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\StageArrow.txt");
    pAnimator->Play(L"StageArrow", true);
    m_arrow[0] = arrow;
    m_StageArrow->AddChildUI(arrow);

    // 스테이지 커서 위 화살표
    arrow = new CAnimUI;
    arrow->SetScale({ 3, 5 });
    arrow->SetPos({ 0, 50 });
    pAnimator = arrow->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\StageArrow_d.txt");
    pAnimator->Play(L"StageArrow_d", true);
    m_arrow[1] = arrow;
    m_StageArrow->AddChildUI(arrow);
     
    AddObject(UI, m_StageArrow);
    

    


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
    if (m_isSelect) {
        if (KEY_TAP(ESC)) {
            StageSelectCancel();
        }
    }
    else {
        if (KEY_TAP(RIGHT)) {
            StageCursorNext();
        }
        if (KEY_TAP(LEFT)) {
            StageCursorPrev();
        }

        if (KEY_TAP(ENTER)) {
            StageSelect();
        }

    }
    

}



void CStageSelectLevel::StageCursorNext()
{
    m_cursorIdx++;
    if (m_vecStages.size() <= m_cursorIdx) {
        m_cursorIdx = 0;
    }
    CStage* pStage = m_vecStages[m_cursorIdx];

    m_StageArrow->MoveTo(pStage->GetPos());
    CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x + pStage->GetCameraOffsetX(), float(CEngine::GetInst()->GetResolution().y / 2.f)}, 0.15f);


}


void CStageSelectLevel::StageCursorPrev()
{
    m_cursorIdx--;
    if (m_cursorIdx < 0) {
        m_cursorIdx = m_vecStages.size()-1;
    }
    CStage* pStage = m_vecStages[m_cursorIdx];

    m_StageArrow->MoveTo(pStage->GetPos());
    CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x + pStage->GetCameraOffsetX(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
}

void CStageSelectLevel::StageSelect()
{
    m_isSelect = true;
    CStage* pStage = m_vecStages[m_cursorIdx];
    if (pStage->isLeft()) {
        CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x  + pStage->GetSelectOffset(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
    }
    else {
        CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x  - pStage->GetSelectOffset(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
    }
    
    m_arrow[0]->SetAlpha(0);
    m_arrow[1]->SetAlpha(0);
    m_Veil->SetAlpha(120);
}

void CStageSelectLevel::StageSelectCancel()
{
    m_isSelect = false;
    CStage* pStage = m_vecStages[m_cursorIdx];
    CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x + pStage->GetCameraOffsetX(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
    m_arrow[0]->SetAlpha(255);
    m_arrow[1]->SetAlpha(255);
    m_Veil->SetAlpha(0);

}
