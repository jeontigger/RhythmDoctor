#include "pch.h"
#include "CPausePhone.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CSound.h"

CPausePhone::CPausePhone()
{
    m_curBtn = CAssetMgr::GetInst()->LoadTexture(L"PauseTexture", L"texture\\PauseTexture.png");
    m_Veil = CAssetMgr::GetInst()->LoadTexture(L"Veil", L"texture\\blackPixel.png");
    m_Pause = CAssetMgr::GetInst()->LoadTexture(L"PauseText", L"texture\\PauseText.png");
    m_Body = CAssetMgr::GetInst()->LoadTexture(L"PausePhone", L"texture\\PausePhone.png");


	CPausePhone::Btn btn;
	btn.Icon.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseContinue", L"texture\\PauseContinue.png");
    btn.Icon.PosOffset = { 45, 143 };
    btn.Icon.ScaleOffset = { -30, -30};
    btn.Text.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseContinueText", L"texture\\PauseContinueText.png");
    btn.Text.PosOffset = { -5, 100 };
    btn.EnterFunc = []() { return (int)PauseBtn::Continue; };
	m_vecBtns.push_back(btn);

    btn = {};
    btn.Icon.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseRestart", L"texture\\PauseRestart.png");
    btn.Icon.PosOffset = { 43, 143 };
    btn.Icon.ScaleOffset = { -30, -30 };
    btn.Text.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseRestartText", L"texture\\PauseRestartText.png");
    btn.Text.PosOffset = { -5, 100 };
    btn.EnterFunc = []() { return (int)PauseBtn::Replay; };
    m_vecBtns.push_back(btn);

    btn = {};
    btn.Icon.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseSetting", L"texture\\PauseSetting.png");
    btn.Icon.PosOffset = { 43, 143 };
    btn.Icon.ScaleOffset = { -30, -30 };
    btn.Text.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseAudioDelayText", L"texture\\PauseAudioDelayText.png");
    btn.Text.PosOffset = { -5, 100 };
    btn.LeftArrow.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseButtonArrowL", L"texture\\PauseButtonArrowL.png");
    btn.LeftArrow.PosOffset = { 200, 143 };
    btn.LeftArrow.ScaleOffset = { 8, 8};
    btn.LeftFunc = &CPausePhone::audioDelayFast;

    btn.Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"plus", L"texture\\plus.png");
    btn.Value[0].PosOffset = { 215, 143 };
    btn.Value[0].ScaleOffset = { -50, -75 };
    btn.Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(L"_0", L"texture\\_0.png");
    btn.Value[1].PosOffset = { 230, 144 };
    btn.Value[1].ScaleOffset = { -50, -80 };
    btn.Value[2].Texture = CAssetMgr::GetInst()->LoadTexture(L"dot", L"texture\\dot.png");
    btn.Value[2].PosOffset = { 237, 147 };
    btn.Value[2].ScaleOffset = { -48, -60 };
    btn.Value[3].Texture = CAssetMgr::GetInst()->LoadTexture(L"_0", L"texture\\_0.png");
    btn.Value[3].PosOffset = { 244, 144 };
    btn.Value[3].ScaleOffset = { -50, -80 };

    btn.RightArrow.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseButtonArrowR", L"texture\\PauseButtonArrowR.png");
    btn.RightArrow.PosOffset = { 260, 143 };
    btn.RightArrow.ScaleOffset = { 8, 8 };
    btn.RightFunc = &CPausePhone::audioDelaySlow;
    m_vecBtns.push_back(btn);

    btn = {};
    btn.Icon.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseSetting", L"texture\\PauseSetting.png");
    btn.Icon.PosOffset = { 43, 143 };
    btn.Icon.ScaleOffset = { -30, -30 };
    btn.Text.Texture = CAssetMgr::GetInst()->LoadTexture(L"JudgeOffsetText", L"texture\\JudgeOffsetText.png");
    btn.Text.PosOffset = { -5, 100 };
    btn.LeftArrow.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseButtonArrowL", L"texture\\PauseButtonArrowL.png");
    btn.LeftArrow.PosOffset = { 200, 143 };
    btn.LeftArrow.ScaleOffset = { 8, 8 };
    btn.LeftFunc = &CPausePhone::judgeOffsetFast;

    btn.Value[0].Texture = nullptr;
    btn.Value[0].PosOffset = { 225, 143 };
    btn.Value[0].ScaleOffset = { -50, -75 };
    btn.Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(L"_0", L"texture\\_0.png");
    btn.Value[1].PosOffset = { 240, 144 };
    btn.Value[1].ScaleOffset = { -50, -80 };
    /*btn.Value[2].Texture = CAssetMgr::GetInst()->LoadTexture(L"frame", L"texture\\frame.png");
    btn.Value[2].PosOffset = { 240, 144 };
    btn.Value[2].ScaleOffset = { -270, -80 };*/
    

    btn.RightArrow.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseButtonArrowR", L"texture\\PauseButtonArrowR.png");
    btn.RightArrow.PosOffset = { 260, 143 };
    btn.RightArrow.ScaleOffset = { 8, 8 };
    btn.RightFunc = &CPausePhone::judgeOffsetSlow;
    m_vecBtns.push_back(btn);

    btn = {};
    btn.Icon.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseBack", L"texture\\PauseBack.png");
    btn.Icon.PosOffset = { 38, 139 };
    btn.Icon.ScaleOffset = { -170, -125 };
    btn.Text.Texture = CAssetMgr::GetInst()->LoadTexture(L"PauseBackText", L"texture\\PauseBackText.png");
    btn.Text.PosOffset = { -5, 100 };

    btn.EnterFunc = []() { 	return (int)PauseBtn::Quit; };
    m_vecBtns.push_back(btn);

    m_AudioDelay = 0;
    m_JudgeOffset = 0;

    sndSelect = CAssetMgr::GetInst()->LoadSound(L"sndMenuSelect", L"sound\\sndMenuSelect.wav");
    sndOpen = CAssetMgr::GetInst()->LoadSound(L"sndPagerOpen", L"sound\\sndPagerOpen.wav");
    sndClose = CAssetMgr::GetInst()->LoadSound(L"sndMenuClose", L"sound\\sndMenuClose.wav");
    sndCursorMove = CAssetMgr::GetInst()->LoadSound(L"sndCursorMove", L"sound\\sndCursorMove.wav");
}

CPausePhone::~CPausePhone()
{
}

void CPausePhone::begin()
{
    Vec2 vPos = GetPos();
    m_curBtnPos = { vPos.x + 32.f, vPos.y + 132.f };
    m_vTarget = m_curBtnPos;

    m_EnterFunc = m_vecBtns[m_curIdx].EnterFunc;
    m_LeftFunc = m_vecBtns[m_curIdx].LeftFunc;
    m_RightFunc = m_vecBtns[m_curIdx].RightFunc;
}

void CPausePhone::tick(float _dt)
{
}

void CPausePhone::render(HDC _dc)
{

    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    Vec2 vPos = GetPos();
    Vec2 vRenderPos = GetRenderPos();

    CTexture* tex;
    blend.SourceConstantAlpha = 200;
    tex = m_Veil;
    AlphaBlend(_dc
        , 0 ,vPos.y,720, 400
        , tex->GetDC()
        , 0, 0
        , tex->GetWidth(), tex->GetHeight()
        , blend);
    blend.SourceConstantAlpha = 255;

    tex = m_Body;
    AlphaBlend(_dc
        , vPos.x, vPos.y, tex->GetWidth() * 2.f, tex->GetHeight() * 2.f
        , tex->GetDC()
        , 0, 0
        , tex->GetWidth(), tex->GetHeight()
        , blend);

    tex = m_Pause;
    AlphaBlend(_dc
        , vPos.x - 30.f, vPos.y + 60.f, tex->GetWidth() * 1.f, tex->GetHeight() * 1.f
        , tex->GetDC()
        , 0, 0
        , tex->GetWidth(), tex->GetHeight()
        , blend);

    Vec2 offset;
    Vec2 scaleOffset;

    tex = m_curBtn;
    blend.SourceConstantAlpha = 200;
    AlphaBlend(_dc
        , m_curBtnPos.x, m_curBtnPos.y, tex->GetWidth() * 2.0f, tex->GetHeight() * 2.f
        , tex->GetDC()
        , 0, 0
        , tex->GetWidth(), tex->GetHeight()
        , blend);
    if ((m_vTarget - m_curBtnPos).Length() <= 3.f) {
        m_curBtnPos = m_vTarget;
    }
    else {
        m_curBtnPos.y += m_Speed * DT;
    }

    blend.SourceConstantAlpha = 255;
    for (int i = 0; i < m_vecBtns.size(); i++) {

        // 아이콘 출력
        tex = m_vecBtns[i].Icon.Texture;
        offset = m_vecBtns[i].Icon.PosOffset;
        scaleOffset = m_vecBtns[i].Icon.ScaleOffset;
        if (tex != nullptr) {
            AlphaBlend(_dc
                , vPos.x + offset.x, vPos.y + offset.y + i * m_gBtnYLength, tex->GetWidth() + scaleOffset.x, tex->GetHeight() + scaleOffset.y
                , tex->GetDC()
                , 0, 0
                , tex->GetWidth(), tex->GetHeight()
                , blend);
        }


        // 텍스트 출력
        tex = m_vecBtns[i].Text.Texture;
        offset = m_vecBtns[i].Text.PosOffset;
        scaleOffset = m_vecBtns[i].Text.ScaleOffset;
        if (tex != nullptr) {
            AlphaBlend(_dc
                , vPos.x + offset.x, vPos.y + offset.y + i * m_gBtnYLength, tex->GetWidth() + scaleOffset.x, tex->GetHeight() + scaleOffset.y
                , tex->GetDC()
                , 0, 0
                , tex->GetWidth(), tex->GetHeight()
                , blend);
        }

        // 왼쪽 화살표 출력
        tex = m_vecBtns[i].LeftArrow.Texture;
        offset = m_vecBtns[i].LeftArrow.PosOffset;
        scaleOffset = m_vecBtns[i].LeftArrow.ScaleOffset;
        if (tex != nullptr) {
            AlphaBlend(_dc
                , vPos.x + offset.x, vPos.y + offset.y + i * m_gBtnYLength, tex->GetWidth() + scaleOffset.x, tex->GetHeight() + scaleOffset.y
                , tex->GetDC()
                , 0, 0
                , tex->GetWidth(), tex->GetHeight()
                , blend);
        }

        // 밸류 출력
        for(int j =0; j < 4; j++){
            tex = m_vecBtns[i].Value[j].Texture;
            offset = m_vecBtns[i].Value[j].PosOffset;
            scaleOffset = m_vecBtns[i].Value[j].ScaleOffset;
            if (tex != nullptr) {
                AlphaBlend(_dc
                    , vPos.x + offset.x, vPos.y + offset.y + i * m_gBtnYLength, tex->GetWidth() + scaleOffset.x, tex->GetHeight() + scaleOffset.y
                    , tex->GetDC()
                    , 0, 0
                    , tex->GetWidth(), tex->GetHeight()
                    , blend);
            }
        }

        // 오른쪽 화살표 출력
        tex = m_vecBtns[i].RightArrow.Texture;
        offset = m_vecBtns[i].RightArrow.PosOffset;
        scaleOffset = m_vecBtns[i].RightArrow.ScaleOffset;
        if (tex != nullptr) {
            AlphaBlend(_dc
                , vPos.x + offset.x, vPos.y + offset.y + i * m_gBtnYLength, tex->GetWidth() + scaleOffset.x, tex->GetHeight() + scaleOffset.y
                , tex->GetDC()
                , 0, 0
                , tex->GetWidth(), tex->GetHeight()
                , blend);
        }
    }
}

int CPausePhone::Enter()
{
    if (m_EnterFunc != nullptr) {
        sndSelect->Play(false);
        return  (*m_EnterFunc)();
    }
    return -1;
}

void CPausePhone::Right()
{
    if (m_RightFunc != nullptr) {
        sndCursorMove->Play(false);
        (this->*m_RightFunc)();
    }
}

void CPausePhone::Left()
{
    if (m_LeftFunc != nullptr) {
        sndCursorMove->Play(false);
        (this->*m_LeftFunc)();
    }
}

void CPausePhone::Open()
{
    sndOpen->Play(false);
    SetPos({ 352.f, 0.f });
    m_curIdx = 0;
    begin();
}
void CPausePhone::Close()
{
    sndClose->Play(false);
    Vec2 vPos = GetPos();
    SetPos({ 352.f, 500.f });
    m_curBtnPos = { vPos.x + 32.f, vPos.y + 632.f };
    m_vTarget = m_curBtnPos;
}

void CPausePhone::CursorDown()
{
    sndCursorMove->Play(false);
    m_curIdx++;
    if ((UINT)PauseBtn::END <= m_curIdx) {
        m_curIdx = 0;
    }

    Vec2 vPos = GetPos();
    m_Speed = -(m_curBtnPos.y - (vPos.y + 132.f + m_curIdx * m_gBtnYLength)) / 0.12f;
    m_vTarget = { m_curBtnPos.x, vPos.y + 132.f + m_curIdx * m_gBtnYLength };

    m_EnterFunc = m_vecBtns[m_curIdx].EnterFunc;
    m_LeftFunc = m_vecBtns[m_curIdx].LeftFunc;
    m_RightFunc = m_vecBtns[m_curIdx].RightFunc;
}
void CPausePhone::CursorUp()
{
    sndCursorMove->Play(false);
    m_curIdx--;
    if (m_curIdx < 0) {
        m_curIdx = (UINT)PauseBtn::END - 1;
    }

    Vec2 vPos = GetPos();
    m_Speed = -(m_curBtnPos.y - (vPos.y + 132.f + m_curIdx * m_gBtnYLength)) / 0.12f;
    m_vTarget = { m_curBtnPos.x, vPos.y + 132.f + m_curIdx * m_gBtnYLength };

    m_EnterFunc= m_vecBtns[m_curIdx].EnterFunc;
    m_LeftFunc = m_vecBtns[m_curIdx].LeftFunc;
    m_RightFunc = m_vecBtns[m_curIdx].RightFunc;
   
}


void CPausePhone::audioDelaySlow()
{
    if (m_AudioDelay <= 99) {
        m_AudioDelay ++;
        if (0 <= m_AudioDelay) {
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"plus", L"texture\\plus.png");
            int quot = m_AudioDelay  / 10;
            wstring key = L"_" + std::to_wstring(quot);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
            int mod = m_AudioDelay % 10;
            key = L"_" + std::to_wstring(mod);
            path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[3].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
        else {
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"minus", L"texture\\minus.png");
            int quot = -1 * m_AudioDelay / 10;
            wstring key = L"_" + std::to_wstring(quot);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
            int mod = (- 1 * m_AudioDelay ) % 10;
            key = L"_" + std::to_wstring(mod);
            path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[3].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
    }
}

void CPausePhone::audioDelayFast()
{
    if (-99 <= m_AudioDelay) {
        m_AudioDelay--;
        if (0 <= m_AudioDelay) {
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"plus", L"texture\\plus.png");
            int quot = m_AudioDelay / 10;
            wstring key = L"_" + std::to_wstring(quot);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
            int mod = m_AudioDelay % 10;
            key = L"_" + std::to_wstring(mod);
            path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[3].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
        else {
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"minus", L"texture\\minus.png");
            int quot = -1 * m_AudioDelay / 10;
            wstring key = L"_" + std::to_wstring(quot);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
            int mod = ( - 1 * m_AudioDelay) % 10;
            key = L"_" + std::to_wstring(mod);
            path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::AudioDelay].Value[3].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
    }
    
}

void CPausePhone::judgeOffsetSlow()
{
    if (m_JudgeOffsetToFrame < 5) {
        m_JudgeOffset += 0.016f;
        m_JudgeOffsetToFrame++;
        
        if (0 <= m_JudgeOffsetToFrame) {
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[0].Texture = nullptr;
            wstring key = L"_" + std::to_wstring(m_JudgeOffsetToFrame);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
        else {
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"minus", L"texture\\minus.png");
            wstring key = L"_" + std::to_wstring(-m_JudgeOffsetToFrame);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
        
    }
    
}

void CPausePhone::judgeOffsetFast()
{
    if (-5 < m_JudgeOffsetToFrame) {
        m_JudgeOffset -= 0.016f;
        m_JudgeOffsetToFrame--;
        if (0 <= m_JudgeOffsetToFrame) {
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[0].Texture = nullptr;
            wstring key = L"_" + std::to_wstring(m_JudgeOffsetToFrame);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);

        }
        else {
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[0].Texture = CAssetMgr::GetInst()->LoadTexture(L"minus", L"texture\\minus.png");
            wstring key = L"_" + std::to_wstring(-m_JudgeOffsetToFrame);
            wstring path = L"texture\\" + key + L".png";
            m_vecBtns[(UINT)PauseBtn::JudgeOffset].Value[1].Texture = CAssetMgr::GetInst()->LoadTexture(key, path);
        }
    }
}
