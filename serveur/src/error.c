#include <stdio.h>
#include "ft_irc.h"

void        usage(char *name)
{
    dprintf(2, "usage: %s port", name);
}

int         r_error(char *error)
{
    dprintf(2, "%s", error);
    return (1);
}
