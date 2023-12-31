﻿#pragma once
#include "CObj.h"

enum class Stage_Type {
    SAMURAI,
    END
};

enum class Stage_Rank {
    A,
    UNCOMPLETED,
    COMPLETED,
    END
};

class CStage :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    wstring m_strLevel;
    wstring m_strName;
    wstring m_strCharacterName;
    wstring m_strRank;
    Stage_Rank m_Rank;
    int m_iDifficulty;
    wstring m_strDescription;
    bool m_bIsBoss;
    bool m_isSelected;

    float m_fStrOffset;
    float m_fStrDiff;

    Vec2 m_CameraOffset;

    bool m_isStageSelectLeft;
    float m_fSelectCameraOffset;

    class CTexture* m_StageTex;
    Vec2 m_vTexOffset;
    bool m_isHover;
    class CTexture* m_PhoneTex;

public:
    virtual void tick(float _dt) override;
    virtual void render(HDC _dc) override;
    void SetRank(Stage_Rank _rank);
    void SetLevel(wstring _level) { m_strLevel = _level; }
    void SetStageName(wstring _name) { m_strName = _name; }
    wstring& GetStageName() { return m_strName; }
    void SetCharacterName(const wstring& _name) { m_strCharacterName = _name; }
    const wstring& GetCharcaterName() { return m_strCharacterName; }

    void SetDescription(wstring _desc) { m_strDescription = _desc; }
    const wstring& GetDescription() { return m_strDescription; }
    void SetBoss(bool _boss) { m_bIsBoss = _boss; }
    void SetSelected(bool _selected) { m_isSelected = _selected; }

    float GetCameraOffsetX() { return m_CameraOffset.x; }
    void SetCameraOffset(Vec2 _vec) { m_CameraOffset = _vec; }

    float GetSelectOffset() { return m_fSelectCameraOffset; }
    bool isLeft() { return m_isStageSelectLeft; }
    void SetIsLeft(bool _left) { m_isStageSelectLeft = _left; }

    void SetTexture(class CTexture* _tex) { m_StageTex = _tex; }
    void SetTextureOffset(Vec2 _v) { m_vTexOffset = _v; }

    void SetHover(bool _b) { m_isHover = _b; }
    void SetPhoneTexture(class CTexture* _tex) { m_PhoneTex = _tex; }
    class CTexture* GetPhoneTexture() { return m_PhoneTex; }

public:
    CLONE_DISABLE(CStage);
    CStage();
    ~CStage(); 
};

