#pragma once
#include "CLevel.h"
class CStagePlayLevel :
    public CLevel
{

private:
    class CJudgeBar* m_bar;
    class CCharacter* m_Character;
    class CCharacter* m_Heart;


public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

public:
    CStagePlayLevel();
    ~CStagePlayLevel();
};

