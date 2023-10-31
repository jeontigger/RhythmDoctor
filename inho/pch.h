#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN 

#include <windows.h>

#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <tchar.h>
#include <crtdbg.h>
#include <assert.h>

#include <list>
#include <map>
#include <string>
#include <vector>

#pragma comment(lib, "Msimg32.lib")

#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace::Gdiplus;

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

using std::list;
using std::make_pair;
using std::map;
using std::string;
using std::vector;
using std::wstring;

#include "global.h"