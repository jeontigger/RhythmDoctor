#pragma once
#include "CUI.h"
class CTextUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    wstring m_Text;

public:
    virtual void render(HDC _dc) override;
    void SetText(const wstring& _str) { m_Text = _str; }

public:
    CLONE(CTextUI);
    CTextUI();
    CTextUI(const CTextUI& _Origin);
    ~CTextUI();


};

