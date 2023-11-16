#pragma once
#include "CEvent.h"
class CObjEvent :
    public CEvent
{

    GENERATED_OBJECT(CEvent);

public:
    void LoadEventData(const wstring& _strRelativePath, list<ObjInfo>& _out);

    virtual void Play() override;
    virtual void tick(float _dt) override;

public:
    CLONE_DISABLE(CEvent);
    CObjEvent();
    ~CObjEvent();
};

