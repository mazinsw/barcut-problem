#ifndef _TEXTSTREAM_H_
#define _TEXTSTREAM_H_
#include "Buffer.h"

class TextStream: public Buffer
{
private:
    char tmp_buf[1024];
public:
    const char * text() const;
    size_t read(char * buf, size_t size);
    size_t length();
    size_t print(const char * str);
    size_t printf(const char * fmt, ...);
};

#endif