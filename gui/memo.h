#ifndef _MEMO_H_
#define _MEMO_H_

#include "edit.h"

class Memo: public Edit
{
protected:
    DWORD getStyle();
};

#endif
