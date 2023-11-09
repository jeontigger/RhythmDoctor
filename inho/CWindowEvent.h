#pragma once
#include "CEvent.h"

enum class WindowEventType {
    LinearMove,
    END
};
class CWindowEvent :
    public CEvent
{
    GENERATED_OBJECT(CEvent);
private:

    HWND m_hWnd;
    Vec2 m_vMonitorRes;
    Vec2 m_vWinRes;
    Vec2 m_vWinPos; 

    void(CWindowEvent::* pFunc)(float);


private:
        Vec2 m_vTarget;
        float m_fSpeed;
        bool m_bIsAlive;
        void LinearMove(float _dt);

public:
    void SetTarget(Vec2 _target, float _time = 0);

public:
    void SetMode(WindowEventType _type);
    Vec2 GetPos() { return m_vWinPos; }
    void SetPos(Vec2 _pos) { 
        m_vWinPos = _pos;
        MoveWindow(m_hWnd, _pos.x, _pos.y, m_vWinRes.x, m_vWinRes.y, TRUE); }

public:
    virtual void Play() override;
    virtual void tick(float _dt) override;

public:
    CLONE(CWindowEvent);
    CWindowEvent();
    ~CWindowEvent();
};

