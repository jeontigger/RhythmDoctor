#pragma once
#include "CLevel.h"

class CStartMenuLevel :
    public CLevel
{
private:
    class CAnimUI* m_Monitor;
    vector<class CTextUI*> m_vecMenus;
    class CTextUI* m_AnyPress;
    int m_curIdx;

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

