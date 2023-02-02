#pragma once

//경고 무시
// ㄴ 4005: DXGI 등 그래픽 인터페이스에서 매크로 관련하여 많이 출력되는 경고
#pragma warning(disable : 4005)

// 거의 사용되지 않는 내용을 Windows 헤더에서 제외
#define WIN32_LEAN_AND_MEAN
// GDI+를 사용하려면 헤더파일 꺼내와야 한다
// ㄴ <ole2.h>

//! Windows 헤더 파일
#include <windows.h>

//! 디버깅용 콘솔창
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! 라이브러리 링크
#pragma comment (lib, "msimg32.lib") //마이크로소프트(ms) 이미지(img) 32비트(32) 라이브러리
#pragma comment (lib,"winmm.lib")
#pragma comment (lib, "lib/FMOD/fmod_vc.lib")
//#pragma comment (lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")

#include "inc/FMOD/fmod.hpp"
//#include "JsonCPP/include/json/json.h"
#include <SDKDDKVer.h>

//! OpenGL 헤더 파일
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>


// =====================
//! C 런타임 헤더 파일
// =====================
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <MMSystem.h>


// =====================
//! C++ 런타임 헤더 파일
// =====================
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <functional>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;
//using std::vector;
//using std::bitset;



// =====================
//! 사용자 정의 헤더파일
// =====================
#include "CommonMacroFunction.h"  
#include "RandomFunction.h"
#include "KeyManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "GLAPI.h"

using namespace MY_UTIL;


// =====================
//! 싱글톤
// =====================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()


//==============================
// # 매크로 # (윈도우창 초기화)
//==============================

//! 전체 화면
//#define FULL_SCREEN

#ifdef FULL_SCREEN

#define WIN_NAME (LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X 0
#define WINSTART_Y 0
//GetSystemMetrics(): 인자로 전달되는 시스템 설정 정보를 반환한다.
	//ㄴ SM_CXSCREEN: 현재 화면 기준 해상도 x축 반환
	//ㄴ SM_CYSCREEN: 현재 화면 기준 해상도 y축 반환
#define WINSIZE_X GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y GetSystemMetrics(SM_CYSCREEN)
//WS_POPUPWINDOW: 팝업 윈도우 생성
// WS_MAXIMIZE: 윈도우 사이즈 최대화
#define WINSTYLE WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WIN_NAME (LPSTR)(TEXT("Hades"))
#define WINSTART_X 400
#define WINSTART_Y 100
#define WINSIZE_X 1600
#define WINSIZE_Y 900
#define WINSIZE_PT Point2D(1600, 900)
#define WINSTYLE WS_OVERLAPPED | WS_SYSMENU

#endif

//==============================
// # 매크로 함수 #
//==============================
#define SAFE_DELETE(p)       {if(p){delete(p); (p) = nullptr;}}   //안전하게 초기화
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=nullptr;}}  //복수 객체일 경우
#define SAFE_RELEASE(p)      {if(p) {(p)->release();(p)=nullptr;}

//==============================
// # 전역 변수 #
//==============================
//X좌표와 Y좌표를 평면의 좌표에 정의할 때 사용 -2D에서 좌표 표현 적합
extern Point2D _ptMouse;
