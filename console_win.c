#include <windows.h>

#define WCLASSNAME "Tantrix Window"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS wc;
    MSG msg;

    ZeroMemory(&wc, sizeof(WNDCLASS));
    wc.style            = CS_OWNDC | WS_OVERLAPPED;
    wc.hbrBackground    = (HBRUSH) (COLOR_WINDOW);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(NULL, IDC_ICON);
    wc.lpszClassName    = WCLASSNAME;
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;

     

    return 0;
}

