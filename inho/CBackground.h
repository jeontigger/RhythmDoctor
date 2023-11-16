#pragma once
#include "CObj.h"

#include "CTexture.h"

class CBackground :
    public CObj
{
private:
    class CTexture* m_Tex;
    
public:
    void SetTexture(const wstring& _strKey, const wstring& _strRelativePath);
    void SetTexture(class CTexture* _tex);
    UINT GetWidth() { return m_Tex->GetWidth(); }
    UINT GetHeight() { return m_Tex->GetHeight(); }

public:
    virtual void render(HDC _dc) override;
public:

    CLONE_DISABLE(CBackground);
    CBackground();
    ~CBackground();

};

