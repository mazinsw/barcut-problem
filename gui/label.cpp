#include "label.h"

Label::Label()
{
    autoSize = true;
}

bool Label::create(int x, int y, int width, int height,
            String text, Control * parent)
{
    if(!createControl(0, 0, "Static", text, x, y, width, height, parent))
        return false;

    return true;
}

void Label::resize(int width, int height)
{
    if(autoSize)
    {
        SIZE sz;
        HDC hDC;
        
        hDC = GetDC(getHandle());
        sz.cx = getFont().getWidth(hDC, getText());
        sz.cy = getFont().getHeight(hDC);
        SetWindowPos(getHandle(), 0, 0, 0, sz.cx, sz.cy, SWP_NOMOVE);
        ReleaseDC(getHandle(), hDC);
        invalidate();
    }

}

LRESULT Label::message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg == WM_SETFONT || uMsg == WM_SETTEXT)
    {
        LRESULT ret = Control::message(uMsg, wParam, lParam);
        if(autoSize)
            resize(1, 1);
        return ret;
    }
    return Control::message(uMsg, wParam, lParam);
}

