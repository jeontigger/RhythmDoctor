#include "pch.h"
#include "CStageSelectLevel.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"


//
#include "CBackground.h"
//
void CStageSelectLevel::init()
{

    // 배경 생성
    CBackground* pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBG", L"texture\\StageSelectLevelBG_L.png");
    pBg->SetPos({ (float)pBg->GetWidth() - 740.f, 125.f});
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);

    pBg = new CBackground;
    pBg->SetTexture(L"StageSelectBG", L"texture\\StageSelectLevelBG_R.png");
    pBg->SetPos({ (float)pBg->GetWidth() + 279.f, 125.f });
    pBg->SetScale({ 2,2 });
    AddObject(BACKGROUND, pBg);


    // 카메라 설정
    Vec2 vLookAt = CEngine::GetInst()->GetResolution();
    vLookAt /= 2.f;
    CCamera::GetInst()->SetLookAt(vLookAt);


}

void CStageSelectLevel::enter()
{
    CCamera::GetInst()->FadeIn(1.0f);

    /*CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
    pSound->SetVolume(100);
    pSound->SetPosition(45.f);
    pSound->Play(true);*/
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
