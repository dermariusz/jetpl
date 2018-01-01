#include "jetpl-token.h"

#include <stdlib.h>

void jetpl_token_update_position(JeTplToken * self, size_t begin, size_t end, int diff)
{
    if (self->begin > begin && self->end > end) {
        self->begin += diff;
        self->end   += diff;
    }
}
