#include <stdio.h>
#include "ft_irc.h"

void        usage(char *name)
{
    dprintf(2, "usage: %s port\n", name);
}

int         r_error(char *error)
{
    dprintf(2, "%s\n", error);
    return (1);
}
