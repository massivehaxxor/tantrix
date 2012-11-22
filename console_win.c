#include <windows.h>

HANDLE hndConInput, hndConOutput;

int init_console(void)
{
    if (AllocConsole() == FALSE)
        return -1;
    hndConInput     = GetStdHandle(STD_INPUT_HANDLE);
    hndConOutput    = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitle("Tantrix");

    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    if (init_console() < 0)
        MessageBox(NULL, "AllocConsole failed", "Error", MB_OK);
    
    return 0;
}

