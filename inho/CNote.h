#pragma once
#include "CObj.h"

class CNote :
    public CObj
{
    GENERATED_OBJECT(CObj);

protected:
    class CUnitBar* m_bar;

protected:
    float m_StartTime;
    float m_AccTime;
    float m_BeatSpeed;

public:
    void SetBeatSpeed(float _speed) { m_BeatSpeed = _speed; }

public:
    virtual void Play(class CUnitBar* _bar);
    
 public:
    CLONE(CNote);
    CNote();
    ~CNote();

    friend class CUnitBar;
    friend class CStagePlayLevel;
};

