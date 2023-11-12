#pragma once
#include "CLevel.h"


class CStagePlayLevel :
    public CLevel
{
private:
    list<NoteInfo*> m_listNoteInfo;
    list<BarInfo*> m_listBarInfo;

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

