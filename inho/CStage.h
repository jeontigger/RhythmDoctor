#pragma once
#include "CObj.h"

enum class Stage_Type {
    SAMURAI,
    END
};

enum class Stage_Rank {
    A,
    END
};

class CStage :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    wstring m_strLevel;
    wstring m_strName;
    wstring m_strRank;
    Stage_Rank m_Rank;
    int m_iDifficulty;
    wstring m_strDescription;
    bool m_bIsBoss;

    float m_fStrOffset;
    float m_fStrDiff;


public:
    virtual void tick(float _dt) override;
    virtual void render(HDC _dc) override;
    void SetRank(Stage_Rank _rank);
    void SetLevel(wstring _level) { m_strLevel = _level; }
    void SetName(wstring _name) { m_strName = _name; }
    void SetDescription(wstring _desc) { m_strDescription = _desc; }
    void SetBoss(bool _boss) { m_bIsBoss = _boss; }

public:
    CLONE_DISABLE(CStage);
    CStage();
    ~CStage(); 
};

