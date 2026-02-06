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

    testui.initialize("uiclass");
    testui.create(hInstance, "test-ui");

    testui.start();
    return 0;
}