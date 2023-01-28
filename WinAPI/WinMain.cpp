#include "Stdafx.h"
#include "GameEngine.h"
#include "MainGame.h"

// =================
// # ���� ���� #
// =================
HINSTANCE _hInstance;
HWND _hWnd;
Point2D _ptMouse = { 0,0 };

// =================
// # �Լ� ���漱�� #
// =================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD threadUpdate(void);
void setWindowSize(int x, int y, int width, int height);

EngineInit param;
GameEngine* _ge;
MainGame* _mg;

//������ ���� �Լ�
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
    _mg = new MainGame();
    //�ش�Ǵ� �ν��Ͻ��� ���������� ��´�.
    _hInstance = hInstance;

    //������ â ����ü ���� �� �ʱ�ȭ
    WNDCLASSEX wndClass;

    wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; //������ ���� �޸�
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //��׶���. GetStockObject() �����Ҵ� �����ϰ� Ȯ���� �Լ�.
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //���콺Ŀ�� ������
    wndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING); //������
    wndClass.hIconSm = LoadIcon(NULL, IDC_APPSTARTING); 
    wndClass.hInstance = hInstance; //�����츦 ������ ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν���. ���ܹ߻��� ó���ϱ� ���� (WNDPROC)�� ���.
    wndClass.lpszClassName = WIN_NAME; //�𷡽� �̸�(������ Ŭ���� �ĺ��� ����)
    wndClass.lpszMenuName = NULL; //�޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW; //������ ��Ÿ��(������ �ٽñ׸��� ����)

    // ������ Ŭ���� ���
    RegisterClassEx(&wndClass);

#ifdef FULL_SCREEN

    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));
    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;
    dm.dmPelsWidth = 1980;
    dm.dmPelsHeight = 1020;
    dm.dmDisplayFrequency = 60;             //����� 60Hz

    //�츮�� ������ �÷���(�ɼ�) �� ����
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    //ȭ���� ����Ǹ� ���� �ػ󵵷� ����(�ڵ�����)
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    // ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindow
    (
        WIN_NAME, //������ Ŭ���� �ĺ���
        WIN_NAME, //������ Ÿ��Ʋ �� �̸�
        WINSTYLE, //������ ��Ÿ��
        WINSTART_X, //������ ȭ�� x��ǥ
        WINSTART_Y, //������ ȭ�� y��ǥ
        WINSIZE_X, //������ ȭ�� ����ũ��
        WINSIZE_Y, //������ ȭ�� ����ũ��
        NULL, //�θ� ������ ��������.
        (HMENU)NULL, //�޴� �ڵ�
        hInstance, //�ν��Ͻ� ����
        NULL //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �ƴ϶�� NULL. - �ʿ信 ���� ��������� ������ NULL
    );

    // Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ��´�.
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#else

    // ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindowEx
    (
        0,
        WIN_NAME, //������ Ŭ���� �ĺ���
        WIN_NAME, //������ Ÿ��Ʋ �� �̸�
        WINSTYLE, //������ ��Ÿ��
        WINSTART_X, //������ ȭ�� x��ǥ
        WINSTART_Y, //������ ȭ�� y��ǥ
        WINSIZE_X, //������ ȭ�� ����ũ��
        WINSIZE_Y, //������ ȭ�� ����ũ��
        NULL, //�θ� ������ ��������.
        (HMENU)NULL, //�޴� �ڵ�
        hInstance, //�ν��Ͻ� ����
        NULL //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �ƴ϶�� NULL. - �ʿ信 ���� ��������� ������ NULL
    );

    // Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ��´�.
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

    // ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hWnd, nCmdShow);

    //���� ���� Ŭ���� �ʱ�ȭ ���� �� ����
    if (FAILED(_mg->init()))
    {
        return 0;
    }

    //MSG: �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü.
    MSG message;

    // 2. �޽��� ����
    
    //���ӿ�
    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT) break;

            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            TIMEMANAGER->update(60.0f);
            _mg->update();
            _mg->render();
        }
    }
    //PM_REMOVE: ���� 1�� 16������ �ٲ� ���� ��. -> �ӵ��� �ø��� ����.

    _mg->release();
    //������ Ŭ���� ��� ����
    UnregisterClass(WIN_NAME, hInstance);
    return message.wParam;
}

//������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (IMessage)
    {
    case WM_CREATE:
    {
        _hWnd = hWnd;
        _ge->engineInitializer(param);
    
        int state = _ge->GetEngineState();
        if (state != GameEngine::OK) {
            MessageBox(hWnd, _ge->GetEngineStateString().c_str(), "Incomplete Engine Init", 0);
            _ge->StopEngine();
        }
        else {
            thread UpdateThread(threadUpdate);
        }
        break;
    }
    case WM_TIMER:
        _ge->engineRender();
        break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
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
        _ge->SetExitThread();
        _ge->engineRelease();
        DestroyWindow(hWnd);
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return (DefWindowProc(hWnd, IMessage, wParam, lParam));
    }
    
    return 0;
}

DWORD threadUpdate(void)
{
    LARGE_INTEGER begin, end;
    LARGE_INTEGER freq;
    ulong elapsed, delay;

    QueryPerformanceFrequency(&freq);
    while (!_ge->GetExitThread()) {
        QueryPerformanceCounter(&begin);
        _ge->engineUpdate();
        QueryPerformanceCounter(&end);
        elapsed = (end.QuadPart - begin.QuadPart) * 1000000 / freq.QuadPart;
        if (param.updateDelay > elapsed) {
            delay = (param.updateDelay - elapsed) / 1000;
            Sleep(delay);
        }
    }
    return 0;
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width,height };

    //���� ������ ũ�� ����
    //AdjustWindowRect() : ��� ��ü, ����� ������ ��Ÿ��, �޴� ����
    AdjustWindowRect(&rc, WINSTYLE, false);

    //���� ��Ʈ�� ������ ������ ������ ����
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
    //ZORDER : ��ü���� �������� �� ���̾� ���� ������ ���� ���(������). ���ӿ��� ���� ���δ�.
    //�츮 ȭ���� ���� �տ� ���ڴ�. (����)
}