#pragma once

#define SINGLETON(ClassType)                                                   \
  public:                                                                      \
    static ClassType* GetInst() {                                              \
        static ClassType inst;                                                 \
        return &inst;                                                          \
    }                                                                          \
                                                                               \
  public:                                                                      \
    ClassType* operator=(const ClassType& _Origin) = delete;                   \
                                                                               \
  private:                                                                     \
    ClassType();                                                               \
    ClassType(const ClassType& _Origin) = delete;                              \
    ~ClassType();

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)

#define PI 3.14159265348979f
#define GAME_FOLDER MyGame

#define GENERATED_OBJECT(type)                                                 \
    typedef type Super;

#define DEBUG_RENDER CEngine::GetInst()->DebugRender()

#define TILE_SIZE 64

#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone() {return nullptr;}

enum KEY {
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,

    NUM0,
    NUM1,
    NUM2,
    NUM3,
    NUM4,
    NUM5,
    NUM6,
    NUM7,
    NUM8,
    NUM9,

    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,

    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,

    Z,
    X,
    C,
    V,
    B,
    N,
    M,

    TAB,
    LSHIFT,
    LALT,
    LCTRL,
    SPACE,

    ESC,
    ENTER,
    BACK,

    LEFT,
    RIGHT,
    UP,
    DOWN,

    LBTN,
    RBTN,

    KEY_END,
};

enum KEY_STATE {
    NONE,
    TAP,
    PRESSED,
    RELEASED,
};

enum LAYER {
    DEFAULT,
    BACKGROUND,
    TILE,
    PLATFORM,
    PLAYER,
    MONSTER,
    PLAYER_PJ,
    MONSTER_PJ,
    WORLD_STATIC,

    STAGE,
    HAND,
    UI = 31,
    END = 32,
};

enum TASK_TYPE {
    // Param1 : Layer Type, Param2 : Object Adress
    CREATE_OBJECT,

    // Param1 : Object Adress
    DELETE_OBJECT,

    LEVEL_CHANGE,
};

enum LOG_LEVEL {
    LOG,
    WARNING,
    ERR,
};

enum class LEVEL_TYPE {
    START_MENU_LEVEL,
    STAGE_SELECT_LEVEL,
    STAGE_PLAY_LEVEL,
    EDITOR_LEVEL,
    END,
};

enum class ENORMAL_MON_STATE {
    IDLE,
    TRACE
};

enum class PauseBtn {
    Continue,
    Replay,
    AudioDelay,
    JudgeOffset,
    Quit,
    END
};

#define CheckPosAndScale Vec2 vPos = GetPos();\
Vec2 vScale = GetScale();\
if (KEY_TAP(KEY::W)) {\
    SetPos({ vPos.x, vPos.y - 1 });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::S)) {\
    SetPos({ vPos.x, vPos.y + 1 });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::A)) {\
    SetPos({ vPos.x - 1, vPos.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::D)) {\
    SetPos({ vPos.x + 1, vPos.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetPos().x) + L" y: " + std::to_wstring(GetPos().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
\
if (KEY_TAP(KEY::UP)) {\
    SetScale({ vScale.x, vScale.y + 1.f });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::DOWN)) {\
    SetScale({ vScale.x, vScale.y - 1.f });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::LEFT)) {\
    SetScale({ vScale.x - 1.f, vScale.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}\
if (KEY_TAP(KEY::RIGHT)) {\
    SetScale({ vScale.x +1.f, vScale.y });\
    wstring buffer = L"";\
    buffer += L"vPos x : " + std::to_wstring(GetScale().x) + L" y: " + std::to_wstring(GetScale().y);\
    CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });\
}