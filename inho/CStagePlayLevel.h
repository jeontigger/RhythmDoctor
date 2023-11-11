#pragma once
#include "CLevel.h"


class CStagePlayLevel :
    public CLevel
{
private:
    list<NoteInfo*> m_listNoteInfo;

private:
    class CUnitBar* m_UnitBar;
    class CCharacter* m_Hand;

private:
    float m_AccTime;

public:
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

