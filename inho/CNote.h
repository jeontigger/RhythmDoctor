#pragma once
#include "CObj.h"

enum class NoteType {
    NORMAL,
    GETSET,
    END
};
class CNote :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    NoteType m_Type;
    float m_AccTime;
    float m_Beat;

public:
    virtual void tick(float _dt) override;


public:
    CLONE(CNote);
    CNote();
    ~CNote();
};

