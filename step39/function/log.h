#include "function.h"

#ifndef _LOG_H_
#define _LOG_H_

typedef struct log {
  Function function;
} Log;

void Log_init(Log* p_self);

#endif // _SUBH_