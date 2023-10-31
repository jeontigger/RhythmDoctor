#pragma once
#include "CObj.h"
class CBackground :
    public CObj
{
private:
    class CTexture* m_Tex;

public:
    void SetTexture(const wstring& _strKey, const wstring& _strRelativePath);

public:
    virtual void render(HDC _dc) override;
    virtual void tick(float _dt) override;

public:

    CLONE_DISABLE(CBackground);
    CBackground();
    ~CBackground();

};

