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
    m_Veil(nullptr),
    SpotlightPos(200.f, 564.f),
    PhonePos(0, 210)
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
    pBg->SetPos({ 23.f, 380.f});
    pBg->SetScale({ 510,148 });
    AddObject(BACKGROUND, pBg);
    veilWidth += pBg->GetWidth();

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBGR", L"texture\\StageSelectLevelBG_R.png");
    pBg->SetPos({ 1529.f, 623.f });
    pBg->SetScale({ 996,148 });
    AddObject(BACKGROUND, pBg);
    veilWidth += pBg->GetWidth();

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectLight", L"texture\\StageSelectLight.png");
    pBg->SetPos({ 532.f, 635.f });
    pBg->SetScale({ 1020, 148 });
    pBg->SetAlpha(150);
    AddObject(BACKGROUND, pBg);

    m_Veil = new CBackground;
    m_Veil->SetName(L"LEVEL_VAIL");
    m_Veil->SetTexture(L"Spotlight", L"texture\\Spotlight.png");
    m_Veil->SetPos(SpotlightPos);
    m_Veil->SetScale({ 800.f, 71.f });
    m_Veil->SetAlpha(0);
    AddObject(BACKGROUND, m_Veil);

    // 사무라이
    CStage* pStage = new CStage;
    pStage->SetPos({-200, Stage_YPosValue });
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
    pStage->SetPos({ 100, Stage_YPosValue });
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
     
    m_Phone = new CAnimUI;
    CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SelectPhone", L"texture\\SelectPhone.png");
    pAnimator = m_Phone->GetComponent<CAnimator>();
    pAnimator->CreateAnimation(L"SelectPhone", pAtlas, Vec2(0, 0), Vec2(160, 205), Vec2(0, 0), 0.3f, 1);
    pAnimator->SaveAnimation(L"animdata");
    //pAnimator->LoadAnimation(L"animdata\\SelectPhone.txt");
    pAnimator->Play(L"SelectPhone", true);
    m_Phone->SetPos(PhonePos);
    m_Phone->SetName(L"Phone");
    m_Phone->SetAlpha(0);
    m_Phone->SetScale({ 160, 205 });

    AddObject(UI, m_Phone);

    

    
    

    


    // 카메라 설정
    Vec2 vLookAt = CEngine::GetInst()->GetResolution();
    vLookAt /= 2.f;
    CCamera::GetInst()->SetLookAt(vLookAt);
    StageCursorNext();
    StageCursorPrev();
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
        m_Veil->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset()+SpotlightPos.x - 400.f, SpotlightPos.y});
        m_Phone->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset() +160.f, PhonePos.y});
    }
    else {
        CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x  - pStage->GetSelectOffset(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
        m_Veil->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset() + SpotlightPos.x - 400.f, SpotlightPos.y });
        m_Phone->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset() - 520.f, PhonePos.y });
    }
    
    m_arrow[0]->SetAlpha(0);
    m_arrow[1]->SetAlpha(0);
    m_Phone->SetAlpha(255);
    m_Veil->SetAlpha(150);
    m_vecStages[m_cursorIdx]->SetSelected(true);
}

void CStageSelectLevel::StageSelectCancel()
{
    m_isSelect = false;
    CStage* pStage = m_vecStages[m_cursorIdx];
    CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x + pStage->GetCameraOffsetX(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
    m_arrow[0]->SetAlpha(255);
    m_arrow[1]->SetAlpha(255);
    m_Veil->SetAlpha(0);
    m_Phone->SetAlpha(0);
    
    m_vecStages[m_cursorIdx]->SetSelected(false);
}

