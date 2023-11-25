#pragma once
#include "CObj.h"


constexpr int m_gBtnYLength = 40;

class CPausePhone :
    public CObj
{
    GENERATED_OBJECT(CObj);

    
private:
    struct Tex {
        CTexture* Texture;
        Vec2 PosOffset;
        Vec2 ScaleOffset;
        Tex() :Texture(nullptr) {}
    };

    struct Btn {
        class Tex Icon;
        class Tex Text;
        class Tex LeftArrow;
        class Tex RightArrow;
        class Tex Value[4];
        int (*EnterFunc)(void);
        void (CPausePhone::*LeftFunc)(void);
        void (CPausePhone::*RightFunc)(void);

        Btn() :EnterFunc(nullptr), LeftFunc(nullptr), RightFunc(nullptr) {};
    };

    int m_AudioDelay;
    float m_JudgeOffset;
    int m_JudgeOffsetToFrame;

    int (*m_EnterFunc)(void);
    void (CPausePhone::*m_LeftFunc)(void);
    void (CPausePhone::*m_RightFunc)(void);
    class CTexture* m_Veil;
    class CTexture* m_curBtn;
    class CTexture* m_Pause;
    class CTexture* m_Body;
    vector<Btn> m_vecBtns;

    Vec2 m_vTarget;
    Vec2 m_curBtnPos;
    float m_Speed;
    int m_curIdx;

private:
    class CSound* sndCursorMove;
    class CSound* sndOpen;
    class CSound* sndClose;
    class CSound* sndSelect;

public:

    int Enter();
    void Right();
    void Left();
    void Open();
    void Close();
    void CursorDown();
    void CursorUp();

    float GetAudioDelay() { return float(m_AudioDelay /10.f); }
    float GetJudgeOffset() { return m_JudgeOffset; }

public:
    virtual void begin() override;
    virtual void tick(float _dt) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(CPausePhone);
    CPausePhone();
    ~CPausePhone();

private:
    void audioDelaySlow();
    void audioDelayFast();
    void judgeOffsetSlow();
    void judgeOffsetFast();
};

