#pragma once
#include "CEvent.h"

class CNote :
    public CEvent
{
protected:
    class CUnitBar* m_bar;

protected:
    
    float m_AccTime;
    float m_BeatSpeed;

public:
    void SetBar(class CUnitBar* _bar) { m_bar = _bar; }
    
    void SetBeatSpeed(float _speed) { m_BeatSpeed = _speed; }

 public:
    CNote();
    ~CNote();
};

