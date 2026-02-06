#ifndef TEST_UI
#define TEST_UI

#include <windows.h>

class testui
{
public:
    void initialize(LPCSTR ClassName)
    {
        this->m_wc.lpfnWndProc = WndProc;
        this->m_wc.hInstance = this->m_hInstance;
        this->m_wc.lpszClassName = ClassName;
        this->m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        this->m_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        
        RegisterClass(&this->m_wc);
    }
    void create(::HINSTANCE hInstance, LPCSTR title, int width = 800, int height = 600)
    {
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);

        ::HWND hwnd = CreateWindowA(this->m_wc.lpszClassName, title, WS_OVERLAPPEDWINDOW, (x - width) / 2, (y - height) / 2, width, height, NULL, NULL, hInstance, NULL);

        ShowWindow(hwnd, SW_SHOW);
    }
    int start()
    {
        BOOL bRet;
        MSG  msg;
        for(;bRet = GetMessage(&msg, NULL, 0, 0);) 
        {
            if (bRet == -1) return msg.wParam;
            if (bRet ==  0) return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return msg.wParam;
    }
private:
    static LRESULT CALLBACK WndProc(::HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch(msg) 
        {
            case WM_LBUTTONDOWN:
            {
                WORD x = LOWORD(lParam);
                WORD y = HIWORD(lParam);
                return 0;
            }
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    
    ::HINSTANCE m_hInstance = GetModuleHandle(nullptr);
    ::WNDCLASS  m_wc{};
};

#endif