#pragma once

struct Vec2 {
  public:
    float x;
    float y;

  public:
    Vec2() : x(0.f), y(0.f) {}

    Vec2(float _x, float _y) : x(_x), y(_y) {}

    Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}

    Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}

    Vec2(UINT _x, UINT _y) : x((float)_x), y((float)_y) {}

    float Distance(const Vec2 _oth) {
        return sqrtf((x - _oth.x) * (x - _oth.x) + (y - _oth.y) * (y - _oth.y));
    }

    float Length() { return sqrtf(x * x + y * y); }

    Vec2& Normalize() {
        float f = Length();
        x /= f;
        y /= f;

        assert(f);
        return *this;
    }
    Vec2 operator -() {
        return Vec2(-x, -y);
    }

    Vec2 operator+(Vec2 _Other) const { return Vec2(x + _Other.x, y + _Other.y); }
    void operator+=(Vec2 _Other) {
        x += _Other.x;
        y += _Other.y;
    }
    Vec2 operator+(float _f) const { return Vec2(x + _f, y + _f); }
    void operator+=(float _f) {
        x += _f;
        y += _f;
    }

    Vec2 operator-(Vec2 _Other) const { return Vec2(x - _Other.x, y - _Other.y); }
    void operator-=(Vec2 _Other) {
        x -= _Other.x;
        y -= _Other.y;
    }
    Vec2 operator-(float _f) const { return Vec2(x - _f, y - _f); }
    void operator-=(float _f) {
        x -= _f;
        y -= _f;
    }

    Vec2 operator*(Vec2 _Other) const { return Vec2(x * _Other.x, y * _Other.y); }
    void operator*=(Vec2 _Other) {
        x *= _Other.x;
        y *= _Other.y;
    }
    Vec2 operator*(float _f) const { return Vec2(x * _f, y * _f); }
    void operator*=(float _f) {
        x *= _f;
        y *= _f;
    }

    Vec2 operator/(Vec2 _Other) const {
        assert(_Other.x);
        assert(_Other.y);
        return Vec2(x / _Other.x, y / _Other.y);
    }
    void operator/=(Vec2 _Other) {
        assert(_Other.x);
        assert(_Other.y);
        x /= _Other.x;
        y /= _Other.y;
    }
    Vec2 operator/(float _f) const { 
        assert(_f);
        return Vec2(x / _f, y / _f);
    }
    void operator/=(float _f) {
        assert(_f);
        x /= _f;
        y /= _f;
    }

    bool operator == (Vec2 _Other) {
        return x == _Other.x && y == _Other.y;
    }

    bool operator != (Vec2 _Other) {
        return !this->operator==(_Other);
    }

    bool IsZero() {
        if (x == 0.f && y == 0.f) {
            return true;
        }
        return false;
    }
};

struct FKeyData {
    KEY       eKey;
    KEY_STATE eState;
    bool      bPressed;
};

struct FMonInfo {
    wchar_t szName[50];
    float   HP;
    float   MP;
    float   Att;
    float   Int;
    float   Speed;
};

struct FTask {
    TASK_TYPE Type;
    UINT_PTR  Param_1;
    UINT_PTR  Param_2;
};

struct FLog {
    LOG_LEVEL Level;
    wstring Message;
    float AccTime;
};

struct NoteInfo {
    wstring Bar;
    float StartTime;
    float GetDuration;
    float Speed;
    float JudgeTime;
    int Cnt;
};

enum StageObj {
    Hand,
    Bar,
    Ting,
    Cole,
    END,
};

struct ObjInfo {
    float StartTime;
    bool Moving;
    float Speed;
    float Duration;
};
enum class WindowEventType {
    /// <summary>
    /// 선형 움직임. SetTarget이 필요함
    /// </summary>
    LinearMove,
    /// <summary>
    /// 원형 움직임. Set Theta, Speed, Radius, CW가 필요함. 추가로 speedDecrease speed를 설정할 수 있음
    /// </summary>
    CircleMove,
    /// <summary>
    /// 지진효과. Set QuakeAmount가 필요함
    /// </summary>
    Quake,
    /// <summary>
    /// 위아래 움직임. Set Target, UDCount, UDSize가 필요함.
    /// </summary>
    UpAndDown,
    /// <summary>
    /// 위로 튕겨 점프하는 움직임. Set jumpsize, jumpspeed, flash가 필요함. 
    /// </summary>
    Jumping,
    /// <summary>
    /// 아래로 숨었다가 원하는 위치로 나타나는 움직임. Set DisapearDistance, DisapearSpeed가 필요함
    /// </summary>
    Disapear,
    /// <summary>
    /// 출렁이는 움직임. Set WaveSpeed, WaveFrequency, WaveSize가 필요함 SetSpeed는 setmode보다 먼저 해야만 함
    /// </summary>
    Wave,
    /// <summary>
    /// 화면 밖을 나가도 돌아오는 움직임. SetPortalDirection, Speed가 필요함
    /// </summary>
    PortalMove,
    /// <summary>
    /// 
    /// </summary>
    END
};
struct WinInfo {
    WindowEventType Type;
    float StartTime;
    Vec2 Target;
    float Speed;
    float Theta;
    float Radius;
    bool CW;
    float Decrease;
    float QuakeAmount = 1;
    bool Flash;
    float Size;
    float Count;
    float Duration;
};