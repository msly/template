#pragma once

#include <windows.h>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

class CWinApplication
{
public:
    CWinApplication(HINSTANCE hInstance, INT iCmdShow);
    virtual ~CWinApplication(void);

public:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static void WndPaint(HDC hdc);
    void Run();

private:
    void RegisterDefaultClass();
    void CreateMainWindow();


    HINSTANCE   m_hInstance;
    INT         m_iCmdShow;
    HWND        m_hWnd;
    ULONG_PTR   m_ulGdiplustoken;

};

typedef void (*PaintEvent)(HDC hdc);
typedef void (*CommandEvent)(WORD NotifyCode, WORD itemID, HWND ctlHandle);

extern PaintEvent   PaintProc;
extern CommandEvent CommandProc;
