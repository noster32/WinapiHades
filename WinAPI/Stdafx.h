#pragma once

//��� ����
// �� 4005: DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ���� ��µǴ� ���
#pragma warning(disable : 4005)

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN
// GDI+�� ����Ϸ��� ������� �����;� �Ѵ�
// �� <ole2.h>

//! Windows ��� ����
#include <windows.h>

//! ������ �ܼ�â
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! ���̺귯�� ��ũ
#pragma comment (lib, "msimg32.lib") //����ũ�μ���Ʈ(ms) �̹���(img) 32��Ʈ(32) ���̺귯��
#pragma comment (lib,"winmm.lib")
#pragma comment (lib, "lib/FMOD/fmod_vc.lib")
//#pragma comment (lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")

#include "inc/FMOD/fmod.hpp"
//#include "JsonCPP/include/json/json.h"
#include <SDKDDKVer.h>

//! OpenGL ��� ����
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>


// =====================
//! C ��Ÿ�� ��� ����
// =====================
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <MMSystem.h>


// =====================
//! C++ ��Ÿ�� ��� ����
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
//! ����� ���� �������
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
//! �̱���
// =====================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()


//==============================
// # ��ũ�� # (������â �ʱ�ȭ)
//==============================

//! ��ü ȭ��
//#define FULL_SCREEN

#ifdef FULL_SCREEN

#define WIN_NAME (LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X 0
#define WINSTART_Y 0
//GetSystemMetrics(): ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ�Ѵ�.
	//�� SM_CXSCREEN: ���� ȭ�� ���� �ػ� x�� ��ȯ
	//�� SM_CYSCREEN: ���� ȭ�� ���� �ػ� y�� ��ȯ
#define WINSIZE_X GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y GetSystemMetrics(SM_CYSCREEN)
//WS_POPUPWINDOW: �˾� ������ ����
// WS_MAXIMIZE: ������ ������ �ִ�ȭ
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
// # ��ũ�� �Լ� #
//==============================
#define SAFE_DELETE(p)       {if(p){delete(p); (p) = nullptr;}}   //�����ϰ� �ʱ�ȭ
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=nullptr;}}  //���� ��ü�� ���
#define SAFE_RELEASE(p)      {if(p) {(p)->release();(p)=nullptr;}

//==============================
// # ���� ���� #
//==============================
//X��ǥ�� Y��ǥ�� ����� ��ǥ�� ������ �� ��� -2D���� ��ǥ ǥ�� ����
extern Point2D _ptMouse;
