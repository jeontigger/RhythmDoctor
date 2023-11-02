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
    class CAnimUI* m_Cursor;
    int m_iCursorIdx;

    bool m_bHeartBeat;
    float m_AccTime;
    float m_Duration;

    class CSound* m_sndCursorMove;
    class CSound* m_sndMenuEnter;
    class CSound* m_sndMenuCancel;
    
    bool m_bOpen;

    vector<class CTextUI*> m_vecMenus;
    class CTextUI* m_AnyPress;
    int m_curIdx;
    class CTextUI* m_curMenu;

private:
    void MoveCursor(int _idx);

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

