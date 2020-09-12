#include "TextStream.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

const char * TextStream::text() const
{
    return (const char *)data();
}

size_t TextStream::read(char* buf, size_t size)
{
    return Buffer::read((char*)buf, size);
}

size_t TextStream::length()
{
    return size();
}

size_t TextStream::print(const char* str)
{
    return Buffer::write((const void*)str, strlen(str));
}

size_t TextStream::printf(const char * fmt, ...)
{
    size_t length;
    va_list args;
    
    va_start(args, fmt);
    length = vsprintf(tmp_buf, fmt, args);
    va_end(args);
    return Buffer::write((const void*)tmp_buf, length);
}
