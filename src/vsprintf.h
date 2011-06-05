#if CHAPTER >= 3
#ifndef VSPRINTF_H
#define VSPRINTF_H

#include <stdarg.h>

int vsprintf(char *buf, const char *fmt, va_list args);

#endif
#endif // CHAPTER >= 3
