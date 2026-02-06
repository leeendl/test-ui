#include "include/test-ui/test-ui.hpp"
#include <stdio.h>

#define DEBUG

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) 
{
#ifdef DEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif

    ::testui testui{};

    testui.initialize(L"一个类");
    testui.create(hInstance, L"我窗口");

    testui.start();
    return 0;
}