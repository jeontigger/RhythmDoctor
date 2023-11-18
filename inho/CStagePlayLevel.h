#pragma once
#include "CLevel.h"

constexpr float JudgeTime = 0.1f;
constexpr float CorrectTime = 0.033f;

enum class BackgroundIndex {
    ColeBack,
    ColeFront,
    Ting,
    TingOpen,
    BVeil,
    MVeil,
    TVeil,
    Noise,
    BlueSky,
    Glitch,

    END,
};

class CStagePlayLevel :
    public CLevel
{

private:
    vector<class CBackground*> m_vecBackGrounds;

private:
    list<WinInfo> m_listWinInfo;
    list<NoteInfo*> m_listNoteInfo;
    list<ObjInfo> m_listObjInfo;
    float m_NoteJudgeTime;
    float m_NoteJudgeTimeOffset;
    bool m_newNote;

private:
    class CUnitBar* m_UnitBar;
    class CCharacter* m_Hand;
    class CCharacter* m_Ting;
    class CCharacter* m_Cole;
    class CCharacter* m_Boss;
    class CCharacter* m_Stage;

private:
    bool m_Paused;
    bool m_bAnyPressed;
    float m_AccTime;

    class CSound* m_BGSound;

private:
    bool Pause();

private:
    float m_curTime;
    void SetMusic(float _time);

public:
    void AnyPress();
    void Judge();

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

public:
    CStagePlayLevel();
    ~CStagePlayLevel();
};

