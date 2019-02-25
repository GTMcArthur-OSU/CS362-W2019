#ifndef _MYASSERT_H
#define _MYASSERT_H

#include <stdbool.h>

void assertEqual(int item1, int item2, bool exitIfFail); // use instead of assert( item1 == item2)
bool assertEqual_bool(int item1, int item2); // use instead of assert( item1 == item2), returns bool

#endif