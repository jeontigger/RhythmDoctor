#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    class CTexture* m_Atlas;
    int m_Idx;

public:
    void SetAtlas(CTexture* _Atlas) { m_Atlas = _Atlas; }
    void SetImgIdx(int _ImgIdx) { m_Idx = _ImgIdx; }
    void AddImgIdx();

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CTile);
    CTile();
    ~CTile();
};

