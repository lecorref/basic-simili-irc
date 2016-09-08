#include "ft_irc.h"

int     is_name_used(t_member **user, char *name)
{
    int     i;
    i = 2;
    while (++i < FD_MAX)
    {
        if (user[i]->status == FD_CLIENT)
        {
            if (!strncmp(user[i]->name, name, 12))
                return (0);
        }
    }
    return (1);
}
