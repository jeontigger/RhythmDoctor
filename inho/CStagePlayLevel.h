#pragma once
#include "CLevel.h"
class CStagePlayLevel :
    public CLevel
{
    
private:
    class CUnitBar* m_Judgebar;
    class CCharacter* m_Hand;

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

