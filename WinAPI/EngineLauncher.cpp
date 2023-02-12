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

    wndClass.hInstance = param.hInstance;                           //�����츦 ������ ���α׷��� �ĺ��� ����
    wndClass.lpszClassName = WIN_NAME;                              //�𷡽� �̸�(������ Ŭ���� �ĺ��� ����)
    wndClass.lpfnWndProc = WndProcEntry;                        //������ ���ν���. ���ܹ߻��� ó���ϱ� ���� (WNDPROC)�� ���.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                       //������ ��Ÿ��(������ �ٽñ׸��� ����)
    wndClass.cbSize = sizeof(WNDCLASSEX);

    wndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING);               //������
    wndClass.hIconSm = LoadIcon(NULL, IDC_APPSTARTING);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //���콺Ŀ�� ������
    wndClass.lpszMenuName = NULL;                                   //�޴� �̸�
    wndClass.cbClsExtra = 0;                                        //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0;                                        //������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //��׶���. GetStockObject() �����Ҵ� �����ϰ� Ȯ���� �Լ�.
    
    if (!RegisterClassEx(&wndClass))
        return 0;

    mainWnd = CreateWindowEx
    (
        0,
        WIN_NAME,                                                   //������ Ŭ���� �ĺ���
        param.title.c_str(),                                        //������ Ÿ��Ʋ �� �̸�
        WINSTYLE,                                                   //������ ��Ÿ��
        WINSTART_X,                                                 //������ ȭ�� x��ǥ
        WINSTART_Y,                                                 //������ ȭ�� y��ǥ
        param.windowSize.x,                                         //������ ȭ�� ����ũ��
        param.windowSize.y,                                         //������ ȭ�� ����ũ��
        NULL,                                               //�θ� ������ ��������.
        NULL,                                                       //�޴� �ڵ�
        param.hInstance,                                            //�ν��Ͻ� ����
        NULL                                                        //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �ƴ϶�� NULL. - �ʿ信 ���� ��������� ������ NULL
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

    //���� ������ ũ�� ����
    AdjustWindowRect(&rc, WINSTYLE, false);

    //���� ��Ʈ�� ������ ������ ������ ����
    SetWindowPos(param._hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}






