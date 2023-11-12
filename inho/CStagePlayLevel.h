#pragma once
#include "CLevel.h"

constexpr float JudgeTime = 0.05f;
constexpr float CorrectTime = 0.016f;

class CStagePlayLevel :
    public CLevel
{
private:
    list<NoteInfo*> m_listNoteInfo;
    list<BarInfo*> m_listBarInfo;
    float m_NoteJudgeTime;
    bool m_newNote;

private:
    class CUnitBar* m_UnitBar;
    class CCharacter* m_Hand;

private:
    bool m_bAnyPressed;
    float m_AccTime;

    class CSound* m_BGSound;

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

