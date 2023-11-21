#pragma once
#include "CObj.h"
class CThermometer :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CTexture* m_TexBossThermometer;
    CTexture* m_TexBossHealthBar;
    CTexture* m_TexUserThermometer;
    CTexture* m_TexUserHealthBar;

private:
    int m_IBossMaxHealth;
    int m_IBossCurHealth;
    int m_IUserMaxHealth;
    int m_IUserCurHealth;

public:
    void SetBossMaxHealth(int _cnt) { m_IBossMaxHealth = _cnt; m_IBossCurHealth = _cnt; }
    void SetUserMaxHealth(int _cnt) { m_IUserMaxHealth = _cnt; m_IUserCurHealth = _cnt; }
    void BossHealthReduce();

    /// <summary>
    /// 유저 현재 체력 감소 
    /// </summary>
    /// <returns>false: 사망</returns>
    bool UserHealthReduce();

public:
    CLONE_DISABLE(CThermometer);
    CThermometer();
    ~CThermometer();
};

