#ifndef TEST_UI_HPP
#define TEST_UI_HPP

#include <windows.h>
#include "object/object.hpp"
#include <stdio.h>
#include <vector>

class testui
{
public:
    void initialize(LPCWSTR ClassName)
    {
        this->m_wc.cbSize = sizeof(this->m_wc);
        this->m_wc.lpfnWndProc = WndProc;
        this->m_wc.hInstance = this->m_hInstance;
        this->m_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        this->m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        this->m_wc.lpszClassName = ClassName;
        
        RegisterClassExW(&this->m_wc);
    }
    void create(::HINSTANCE hInstance, LPCWSTR WindowName, int Width = 800, int Height = 600)
    {
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);

        ::HWND hwnd = CreateWindowExW(0, this->m_wc.lpszClassName, WindowName, WS_OVERLAPPEDWINDOW, (x - Width) / 2, (y - Height) / 2, Width, Height, NULL, NULL, hInstance, this);

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
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
    {
        ::testui *pthis = (::testui*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        
        if (msg == WM_NCCREATE) 
        {
            const ::CREATESTRUCT *pcs = (const ::CREATESTRUCT*)lParam;

            pthis = (::testui*)pcs->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pthis);
        }
        return (pthis) ? pthis->HandleMessage(hwnd, msg, wParam, lParam) : DefWindowProc(hwnd, msg, wParam, lParam);
    }
    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
    {
        switch(msg) 
        {
            case WM_CREATE:
            {
                ::object object{1};
                object.set_size({100, 150}, 100);
                this->m_objects.emplace_back(object);
                
                ::object object{2};
                object.set_size({50, 100}, 100);
                this->m_objects.emplace_back(object);
            }
            case WM_PAINT:
            {
                ::PAINTSTRUCT ps{};
                HDC hdc = BeginPaint(hwnd, &ps);

                for (::object object : this->m_objects)
                {
                    object.circle(hdc, object.axis(), object.diameter().x);
                    object.text(hdc, L"a circle");
                }

                EndPaint(hwnd, &ps);
                return 0;
            }
            case WM_LBUTTONDOWN:
            {
                ::POINT point = {LOWORD(lParam), HIWORD(lParam)};

                for (::object object : this->m_objects)
                    if (object.is_inside(point)) printf("clicked #%d circle!\n", object.m_id/*make fun called get_id()*/);
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
    std::vector<::object> m_objects;

    ::HINSTANCE   m_hInstance = GetModuleHandle(nullptr);
    ::WNDCLASSEXW m_wc;
};

#endif // TEST_UI_HPP