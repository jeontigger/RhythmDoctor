#pragma once
#include "CLevel.h"

constexpr float Stage_YPosValue = 260;
enum class Phone_Text{
    StageName,
    CharacterName,
    Description,
    END
};

enum class Phone_Anim {
    Phone,
    Monitor,
    Paper,
    Band,
    Rank,
    Portrait,
    Star,
    Button,
    Start,
    Hand,
    LArrow,
    RArrow,
    LT,
    RT,
    LB,
    RB,
    END
};

enum class Stage {
    Samurai,
    SamuraiBoss,
    Ting,
    AllTheTime,
    Cole,
    END,
};

class CStageSelectLevel : public CLevel {

private:
    class CAnimUI* m_StageArrow;
    class CAnimUI* m_arrow[2];
    vector <class CAnimUI*> m_vecPhones;
    vector<class CTextUI*> m_vecPhoneTexts;
    vector<class CStage*> m_vecStages;
    bool m_isSelect;
    class CBackground* m_Veil;

    class CCharacter* m_Ting;
    class CCharacter* m_Cole;

    Vec2 SpotlightPos;
    Vec2 PhonePos;

    class CSound* m_BGM;
    class CSound* m_sndCursorMove;
    class CSound* m_sndMenuEnter;
    class CSound* m_sndMenuCancel;
    class CSound* m_sndMenuSelect;

private:
    int m_cursorIdx;
    void StageCursorNext();
    void StageCursorPrev();
    void StageSelect();
    void StageSelectCancel();

    void SetPhoneUIAlpha(int _alpha);

  public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

public:
    CStageSelectLevel();
    ~CStageSelectLevel();

private:
    void TingColeMove();
};
