#include "WinApplication.h"

PaintEvent      PaintProc   = NULL;
CommandEvent    CommandProc = NULL;

CWinApplication::CWinApplication(HINSTANCE hInstance, INT iCmdShow)
    : m_hInstance(hInstance)
    , m_iCmdShow(iCmdShow)
{
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR m_ulGdiplustoken;
    GdiplusStartup(&m_ulGdiplustoken, &gdiplusStartupInput, NULL);
}


CWinApplication::~CWinApplication(void)
{
    GdiplusShutdown(m_ulGdiplustoken);
}

void CWinApplication::RegisterDefaultClass()
{
    WNDCLASS    wndClass;

    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = &CWinApplication::WndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = m_hInstance;
    wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = TEXT("GDITest");

    ::RegisterClass(&wndClass);
}

void CWinApplication::CreateMainWindow()
{
    m_hWnd = ::CreateWindow(
        TEXT("GDITest"),
        TEXT("GDITest"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        static_cast<int>(400*0.618),
        NULL,
        NULL,
        m_hInstance,
        NULL);
}

LRESULT CALLBACK CWinApplication::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC         hdc;
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        WndPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void CWinApplication::WndPaint(HDC hdc)
{
    if (PaintProc)
        PaintProc(hdc);
}

void CWinApplication::Run()
{
    RegisterDefaultClass();
    CreateMainWindow();

    ShowWindow(m_hWnd, m_iCmdShow);
    UpdateWindow(m_hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
