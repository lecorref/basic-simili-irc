#include "client.h"

int         pr_error(const char *error)
{
    dprintf(2, "%s\n", error);
    return (1);
}
