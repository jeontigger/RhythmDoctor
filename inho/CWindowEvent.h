﻿#pragma once
#include "CEvent.h"
enum class PortalDirection {
    Left,
    Top,
    Right,
    Bottom,
    END
};

enum class WindowEventType {
    /// <summary>
    /// 선형 움직임. SetTarget이 필요함
    /// </summary>
    LinearMove,
    /// <summary>
    /// 원형 움직임. Set Theta, Speed, Radius, CW가 필요함. 추가로 speedDecrease speed를 설정할 수 있음
    /// </summary>
    CircleMove,
    /// <summary>
    /// 지진효과. Set QuakeAmount가 필요함
    /// </summary>
    Quake,
    /// <summary>
    /// 위아래 움직임. Set Target, UDCount, UDSize가 필요함.
    /// </summary>
    UpAndDown,
    /// <summary>
    /// 위로 튕겨 점프하는 움직임. Set jumpsize, jumpspeed, flash가 필요함. 
    /// </summary>
    Jumping,
    /// <summary>
    /// 아래로 숨었다가 원하는 위치로 나타나는 움직임. Set DisapearDistance, DisapearSpeed가 필요함
    /// </summary>
    Disapear,
    /// <summary>
    /// 출렁이는 움직임. Set WaveSpeed, WaveFrequency, WaveSize가 필요함
    /// </summary>
    Wave,
    /// <summary>
    /// 화면 밖을 나가도 돌아오는 움직임. SetPortalDirection, Speed가 필요함
    /// </summary>
    PortalMove,
    /// <summary>
    /// 
    /// </summary>
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

private:
    float m_Theta;
    float m_Radius;
    bool m_bCW;
    float m_fRDecSpeed;
    void CircleMove(float _dt);

private:
    int m_QuakeAmount;
    void WindowQuake(float _dt);

private:
    float m_Duration;
    float m_AccTime;
    float m_fUDSize;
    int m_iUDCount;
    int m_curCount;
    void UpAndDown(float _dt);

private:
    Vec2 m_vOrigin;
    bool m_IsUp;
    bool m_IsFall;
    bool m_IsFlash;
    void Jumping(float _dt);

private:
    float m_Distance;
    void Disapear(float _dt);

private:
    float m_fFrequency;
    void Wave(float _dt);

private:
    void Portal(float _dt);

private:
    void Stop(float _dt);

public:
    void SetTarget(Vec2 _target, float _time = 0);
    void SetTheta(float _theta) { m_Theta = _theta; }
    void SetSpeed(float _speed) { m_fSpeed = _speed; }

    void SetRadius(float _r) { m_Radius = _r; }
    void SetCW(bool _cw) { m_bCW = _cw; }
    void SetDecreaseSpeed(float _speed) { m_fRDecSpeed = _speed; }

    void SetQuakeAmount(int _amount) { m_QuakeAmount = _amount; }

    void SetUpDownSize(float _size) { m_fUDSize = _size; }
    void SetUpDownCount(int _cnt) { m_iUDCount = _cnt; }

    void SetJumpingSize(float _size) { m_fUDSize = _size; }
    void SetJumpingSpeed(float _time) { m_Duration = _time; }
    void SetFlash(bool _flash) { m_IsFlash = _flash; }

    void SetDisapearSpeed(float _time) { m_Duration = _time; }
    void SetDisapearDistance(float _dist) { m_Distance = _dist; }

    void SetWaveSize(float _size) { m_fUDSize = _size; }
    void SetWaveSpeed(float _speed) { m_fSpeed = _speed; }
    void SetWaveFrequency(float _freq) { m_fFrequency = _freq; }

    void SetPortalDirection(PortalDirection _dir);
    
public:
    void SetMode(WindowEventType _type);

    Vec2 GetPos() { return m_vWinPos; }
    void SetPos(Vec2 _pos) { 
        m_vWinPos = _pos;
        MoveWindow(m_hWnd, _pos.x, _pos.y, m_vWinRes.x, m_vWinRes.y, TRUE); 
    }

public:
    virtual void Play() override;
    virtual void tick(float _dt) override;

public:
    CLONE(CWindowEvent);
    CWindowEvent();
    ~CWindowEvent();
};

