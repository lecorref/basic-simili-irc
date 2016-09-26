#include "client.h"

int     cmp_chan(void *chan, void *str)
{
    return (!strcmp(((t_channel *)chan)->name, str));
}
