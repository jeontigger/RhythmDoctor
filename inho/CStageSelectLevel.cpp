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
#include "CTextUI.h"
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
#pragma region 배경생성
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
#pragma endregion

#pragma region 스테이지 생성

    // 사무라이
    CStage* pStage = new CStage;
    pStage->SetPos({-200, Stage_YPosValue });
    pStage->SetScale({ 40, 40 });
    pStage->SetBoss(false);
    pStage->SetLevel(L"1-1");
    pStage->SetStageName(L"SamuraiTechno");
    pStage->SetCharacterName(L"사무라이");
    pStage->SetDescription(L"환자의 심장에 가해지던 압력이 해소됨. 클럽에서는 그나마 가벼운 갑옷을 착용하라고 권장하였음.");
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
    pStage->SetStageName(L"BattlewornInsomniac");
    pStage->SetCharacterName(L"사무라이 보스");
    pStage->SetDescription(L"환자가 기운이 살아남! 한참 신이 나서 검을 휘두르기 시작했으니까, 멈출 때까지 가까이 가지 말도록 할 것.");
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

#pragma endregion

#pragma region 휴대폰 UI

    m_vecPhones.resize((UINT)Phone_Anim::END);
    // 휴대폰 추가
    CAnimUI* pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\SelectPhone.txt");
    pAnimator->Play(L"SelectPhone", true);
    pAUI->SetPos(PhonePos);
    pAUI->SetName(L"Phone");
    pAUI->SetScale({ 160, 205 });
    m_vecPhones[(UINT)Phone_Anim::Phone] = pAUI;

    // monitor ♥ 7beats 추가
     pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\PhoneMonitor.txt");
    pAnimator->Play(L"PhoneMonitor", true);
    pAUI->SetScale({ 124, 24 });
    pAUI->SetPos({ 0,-147 });
    m_vecPhones[(UINT)Phone_Anim::Monitor] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // 랭크 종이 추가
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\RankPaper.txt");
    pAnimator->Play(L"RankPaper", true);
    pAUI->SetScale({ 40, 47 });
    pAUI->SetPos({ 140,-107 });
    m_vecPhones[(UINT)Phone_Anim::Paper] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // 랭크 종이 밴드 추가
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\PhoneBand.txt");
    pAnimator->Play(L"PhoneBand", true);
    pAUI->SetScale({ 58, 50 });
    pAUI->SetPos({ 125,-90 });
    m_vecPhones[(UINT)Phone_Anim::Band] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // 랭크 추가
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PaperRankAPlus", L"texture\\PaperRankAPlus.png");
    pAnimator->CreateAnimation(L"PaperRankAPlus", pAtlas, Vec2(0, 0), Vec2(30, 34), Vec2(0, 0), 0.3f, 1);
    pAnimator->SaveAnimation(L"animdata");
    //pAnimator->LoadAnimation(L"animdata\\PaperRankAPlus.txt");
    pAnimator->Play(L"PaperRankAPlus", true);
    pAUI->SetScale({ 30, 34 });
    pAUI->SetPos({ 135,-105 });
    m_vecPhones[(UINT)Phone_Anim::Rank] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // 초상화 추가
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\BattlewornInsomniac.txt");
    pAnimator->LoadAnimation(L"animdata\\SamuraiTechno.txt");
    pAnimator->Play(L"SamuraiTechno", true);
    pAUI->SetScale({ 21, 24 });
    pAUI->SetPos({ -95,-39 });
    m_vecPhones[(UINT)Phone_Anim::Portrait] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // 난이도 별 추가
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\PhoneStar.txt");
    pAnimator->Play(L"PhoneStar", true);
    pAUI->SetScale({ 12, 12 });
    pAUI->SetPos({ -53,-25 });
    m_vecPhones[(UINT)Phone_Anim::Star] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // 시작 버튼 추가
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\PhoneButtonIdle.txt");
    pAnimator->Play(L"PhoneButtonIdle", true);
    pAUI->SetScale({ 110, 12 });
    pAUI->SetPos({ 5,145 });
    m_vecPhones[(UINT)Phone_Anim::Button] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // Start!! 출력 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\Start.txt");
    pAnimator->Play(L"Start", true);
    pAUI->SetScale({ 30, 6 });
    pAUI->SetPos({ 30,145 });
    m_vecPhones[(UINT)Phone_Anim::Start] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // Start!! 손 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\StartHand.txt");
    pAnimator->Play(L"StartHand", true);
    pAUI->SetScale({ 13, 10 });
    pAUI->SetPos({ -40,145 });
    m_vecPhones[(UINT)Phone_Anim::Hand] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // Left Arrow 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\ButtonArrowL.txt");
    pAnimator->Play(L"ButtonArrowL", true);
    pAUI->SetScale({ 13, 10 });
    pAUI->SetPos({ -80,145 });
    m_vecPhones[(UINT)Phone_Anim::LArrow] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // Right Arrow 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\ButtonArrowR.txt");
    pAnimator->Play(L"ButtonArrowR", true);
    pAUI->SetScale({ 13, 10 });
    pAUI->SetPos({ 87 ,145 });
    m_vecPhones[(UINT)Phone_Anim::RArrow] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // LT 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\LT.txt");
    pAnimator->Play(L"LT", true);
    pAUI->SetScale({ 4, 4 });
    pAUI->SetPos({ -105,125 });
    m_vecPhones[(UINT)Phone_Anim::LT] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // RT 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\RT.txt");
    pAnimator->Play(L"RT", true);
    pAUI->SetScale({ 4, 4 });
    pAUI->SetPos({ 115,125 });
    m_vecPhones[(UINT)Phone_Anim::RT] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // LB 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\LB.txt");
    pAnimator->Play(L"LB", true);
    pAUI->SetScale({ 4, 4 });
    pAUI->SetPos({ -105,165 });
    m_vecPhones[(UINT)Phone_Anim::LB] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);

    // RB 생성
    pAUI = new CAnimUI;
    pAnimator = pAUI->GetComponent<CAnimator>();
    pAnimator->LoadAnimation(L"animdata\\RB.txt");
    pAnimator->Play(L"RB", true);
    pAUI->SetScale({ 4, 4 });
    pAUI->SetPos({ 115,165 });
    m_vecPhones[(UINT)Phone_Anim::RB] = pAUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pAUI);



    m_vecPhoneTexts.resize((UINT)Phone_Text::END);

    CTextUI* pTextUI;
    pTextUI = new CTextUI;
    pTextUI->SetText(L"이름자리");
    pTextUI->SetPos({ -120, -97 });
    m_vecPhoneTexts[(UINT)Phone_Text::StageName] = pTextUI;
    //m_vecPhoneTexts.push_back(pTextUI);
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pTextUI);

    pTextUI = new CTextUI;
    pTextUI->SetText(L"캐릭터 이름 자리");
    pTextUI->SetPos({ -67, -60 });
    pTextUI->SetColor(0, 0, 0);
    m_vecPhoneTexts[(UINT)Phone_Text::CharacterName] = pTextUI;
    m_vecPhones[(UINT)Phone_Anim::Phone]->AddChildUI(pTextUI);

    pTextUI = new CTextUI;
    pTextUI->SetText(L"스테이지 설명 자리");
    pTextUI->SetPos({ -117, -5 });
    pTextUI->SetColor(0, 0, 0);
    m_vecPhoneTexts[(UINT)Phone_Text::Description] = pTextUI;
    m_vecPhones[(UINT)Phone_Anim::Phone] ->AddChildUI(pTextUI);

    AddObject(UI, m_vecPhones[(UINT)Phone_Anim::Phone]);
    SetPhoneUIAlpha(0);

#pragma endregion

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
        if (KEY_TAP(ENTER)) {
            CCamera::GetInst()->BlinkIn(.5f);
        }
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
        m_vecPhones[0]->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset() +160.f, PhonePos.y});
    }
    else {
        CCamera::GetInst()->SetLinearLookAt({ pStage->GetPos().x  - pStage->GetSelectOffset(), float(CEngine::GetInst()->GetResolution().y / 2.f) }, 0.15f);
        m_Veil->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset() + SpotlightPos.x - 400.f, SpotlightPos.y });
        m_vecPhones[0]->SetPos({ pStage->GetPos().x + pStage->GetSelectOffset() - 520.f, PhonePos.y });
    }
    m_vecPhoneTexts[(UINT)Phone_Text::StageName]->SetText(pStage->GetStageName());
    m_vecPhoneTexts[(UINT)Phone_Text::CharacterName]->SetText(pStage->GetCharcaterName());
    m_vecPhoneTexts[(UINT)Phone_Text::Description]->SetText(pStage->GetDescription());
    m_vecPhones[(UINT)Phone_Anim::Portrait]->GetAnimator()->Play(pStage->GetStageName(), true);
    
    m_arrow[0]->SetAlpha(0);
    m_arrow[1]->SetAlpha(0);
    SetPhoneUIAlpha(255);
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
    SetPhoneUIAlpha(0);
    
    m_vecStages[m_cursorIdx]->SetSelected(false);
}

void CStageSelectLevel::SetPhoneUIAlpha(int _alpha)
{
    for (int i = 0; i < (UINT)Phone_Anim::END; i++) {
        m_vecPhones[i]->SetAlpha(_alpha);
    }

    for (int i = 0; i < (UINT)Phone_Text::END; ++i) {
        if (_alpha == 255) {
            m_vecPhoneTexts[i]->SetBlink(1.f, 0.f);
        }
        else if (_alpha == 0) {
            m_vecPhoneTexts[i]->SetBlink(0.f, 1.f);
        }
    }
}

