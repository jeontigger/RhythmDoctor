#pragma once
#include "CLevel.h"

constexpr int StartMenuSize = 8;

class CStartMenuLevel :
    public CLevel
{
private:
    class CAnimUI* m_Monitor;
    class CAnimUI* m_Rhythm;
    class CAnimUI* m_Doctor;
    bool m_bHeartBeat;
    float m_AccTime;
    float m_Duration;
    
    bool m_bOpen;

    vector<class CTextUI*> m_vecMenus;
    class CTextUI* m_AnyPress;
    int m_curIdx;

    

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

