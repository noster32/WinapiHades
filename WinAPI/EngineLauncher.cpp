#include "Stdafx.h"
#include "EngineLauncher.h"

bool EngineLauncher::launched = false;
EngineLauncher* EngineLauncher::instance = NULL;
Point2D _ptMouse = { 0,0 };
bool openGLWindowOpen = false;

EngineLauncher::EngineLauncher(GameEngine* instance, EngineInit init) : engine(*instance)
{
    this->param = init;
    this->instance = this;
}

int EngineLauncher::launch()
{
    if (launched)
    {
        MessageBox(mainWnd, "Engine is Already Launched", "Multiple Engine Launch Warning", 1);
        return 0;
    }
    launched = true;
    return InternalLaunch();
}

inline LRESULT EngineLauncher::WndProcEntry(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    return instance->WndProc(hWnd, IMessage, wParam, lParam);
}

DWORD EngineLauncher::ThreadUpdateEntry(void)
{
    return instance->ThreadUpdate();
}

LRESULT EngineLauncher::WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    switch (IMessage)
    {
        case WM_CREATE: {
            param._hWnd = hWnd;
            engine.engineInitializer(param);

            int state = engine.GetEngineState();
            if (state != GameEngine::OK) {
                MessageBox(hWnd, engine.GetEngineStateString().c_str(), "Incomplete Engine Init", 0);
                engine.StopEngine();
            }
            else {
                updateThread = thread(ThreadUpdateEntry);
                SetTimer(hWnd, 1, param.renderDelay / 1000, NULL);
            }
        }
        break;
        case WM_TIMER:
            engine.engineRender();
            break;
        case WM_MOUSEMOVE:
            break;
        case WM_LBUTTONDOWN:
            break;
        case WM_RBUTTONDOWN:
            break;
        case WM_KEYDOWN:
            switch (wParam)
            {
            case VK_LEFT:
                break;

            case VK_RIGHT:
                break;

            case VK_ESCAPE:
                PostMessage(hWnd, WM_DESTROY, 0, 0);
                break;
            }
            break;
        case WM_CLOSE:
            engine.SetExitThread();
            updateThread.join();
            engine.engineRelease();
            
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, IMessage, wParam, lParam);
    }

    return 0;
}

DWORD EngineLauncher::ThreadUpdate(void)
{
    LARGE_INTEGER begin, end;
    LARGE_INTEGER freq;
    ulong elapsed, delay;

    QueryPerformanceFrequency(&freq);
    while (!engine.GetExitThread()) {
        QueryPerformanceCounter(&begin);
        engine.engineUpdate();
        QueryPerformanceCounter(&end);
        elapsed = (end.QuadPart - begin.QuadPart) * 1000000 / freq.QuadPart;
        if (param.updateDelay > elapsed) {
            delay = (param.updateDelay - elapsed) / 1000;
            Sleep(delay);
        }
    }
    return 0;
}


int EngineLauncher::InternalLaunch()
{
    MSG messages;
    WNDCLASSEX wndClass;
    HMENU menu;

    wndClass.hInstance = param.hInstance;                           //원도우를 소유한 프로그램의 식별자 정보
    wndClass.lpszClassName = WIN_NAME;                              //쿨래스 이름(윈도우 클래스 식별자 정보)
    wndClass.lpfnWndProc = WndProcEntry;                        //윈도우 프로시져. 예외발생을 처리하기 위해 (WNDPROC)를 사용.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                       //윈도우 스타일(윈도우 다시그리기 정보)
    wndClass.cbSize = sizeof(WNDCLASSEX);

    wndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING);               //아이콘
    wndClass.hIconSm = LoadIcon(NULL, IDC_APPSTARTING);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //마우스커서 아이콘
    wndClass.lpszMenuName = NULL;                                   //메뉴 이름
    wndClass.cbClsExtra = 0;                                        //클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                        //윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //백그라운드. GetStockObject() 동적할당 가능하게 확장한 함수.
    
    if (!RegisterClassEx(&wndClass))
        return 0;

    mainWnd = CreateWindowEx
    (
        0,
        WIN_NAME,                                                   //윈도우 클래스 식별자
        param.title.c_str(),                                        //윈도우 타이틀 바 이름
        WINSTYLE,                                                   //윈도우 스타일
        WINSTART_X,                                                 //윈도우 화면 x좌표
        WINSTART_Y,                                                 //윈도우 화면 y좌표
        param.windowSize.x,                                         //윈도우 화면 가로크기
        param.windowSize.y,                                         //윈도우 화면 세로크기
        NULL,                                               //부모 윈도우 지정여부.
        NULL,                                                       //메뉴 핸들
        param.hInstance,                                            //인스턴스 지정
        NULL                                                        //윈도우의 자식 윈도우를 생성하면 지정하고 아니라면 NULL. - 필요에 의해 사용하지만 지금은 NULL
    );

    SetWindowSize(WINSTART_X, WINSTART_Y, param.windowSize.x, param.windowSize.y);
    ShowWindow(mainWnd, param.nCmdShow);

   

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

void EngineLauncher::SetWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width,height };

    //실제 윈도우 크기 조절
    AdjustWindowRect(&rc, WINSTYLE, false);

    //얻어온 렉트의 정보로 윈도우 사이즈 셋팅
    SetWindowPos(param._hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}






