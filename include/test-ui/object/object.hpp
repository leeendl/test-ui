#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <windows.h>

class object
{
public:
    void circle(HDC hdc, COLORREF color = RGB(255, 255, 255)) const
    {
        HBRUSH hbrush = CreateSolidBrush(color);
        SelectObject(hdc, hbrush);
        
        Ellipse(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
        
        DeleteObject(hbrush);
    }
    
    bool is_inside(::POINT point) const 
    {
        ::POINT center = {(m_rect.left + m_rect.right) / 2, (m_rect.top + m_rect.bottom) / 2};
        ::POINT offset = {point.x - center.x, point.y - center.y};

        int radius = this->width() / 2;

        return offset.x * offset.x + offset.y * offset.y <= radius * radius;
    }
    
    int width() const { return m_rect.right - m_rect.left; }
    int height() const { return m_rect.bottom - m_rect.top; }
private:
    ::RECT m_rect = {0, 0, 75, 75};
};

#endif