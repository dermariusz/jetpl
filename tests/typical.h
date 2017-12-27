#ifndef TYPICAL_H
#define TYPICAL_H

#include <stdbool.h>

typedef struct _Typical Typical;

Typical *typical_new(const char *name, long value, bool in_ca);

#endif
