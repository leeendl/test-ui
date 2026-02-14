#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <windows.h>

class object
{
public:
    object(unsigned id) : m_id(id) {}
    unsigned m_id;

    void circle(HDC hdc, ::POINT point, LONG size, COLORREF color = RGB(255, 255, 255))
    {
        this->m_rect = {point.x, point.y, point.x + size, point.y + size};

        HBRUSH brush = CreateSolidBrush(color);
        SelectObject(hdc, brush);
        
        Ellipse(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
        
        DeleteObject(brush);
    }
    void text(HDC hdc, LPCWSTR text)
    {
        SIZE size;
        GetTextExtentPoint32W(hdc, text, sizeof(text), &size);
    
        ::POINT scale = {center().x - (size.cx / 2), center().y - (size.cy / 2)}; // scale to fit
        
        TextOutW(hdc, scale.x, scale.y, text, sizeof(text));
    }
    ::POINT axis() const     { return {m_rect.left, m_rect.top}; }
    ::POINT diameter() const { return {m_rect.right - m_rect.left, m_rect.bottom - m_rect.top}; }
    ::POINT center() const   { return {(m_rect.left + m_rect.right) / 2, (m_rect.top + m_rect.bottom) / 2}; }
    
    bool is_inside(::POINT point) const 
    {
        ::POINT offset = {point.x - center().x, point.y - center().y};
        LONG    radius = this->diameter().x / 2;

        return offset.x * offset.x + offset.y * offset.y <= radius * radius;
    }
    void set_size(::POINT point, LONG size) { this->m_rect = {point.x, point.y, point.x + size, point.y + size}; }
private:
    ::RECT m_rect;
};

#endif