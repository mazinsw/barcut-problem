#include "memo.h"

DWORD Memo::getStyle()
{
    return Edit::getStyle() | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL;
}
