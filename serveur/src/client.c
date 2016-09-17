#include "ft_irc.h"

int     find_name(t_member **user, char *name)
{
    int     i;

    i = 2;
    while (++i < FD_MAX)
    {
        if (user[i]->status == FD_CLIENT)
        {
            if (!strncmp(user[i]->name, name, 12))
                return (i);
        }
    }
    return (0);
}

int     cmp_user(void *user, void *name)
{
    return !strncmp(((t_member *)user)->name, (char *)name, 12);
}

void    get_client_name(t_server *serv, t_cmd cmd, t_member **user, int fd)
{
    (void)serv;
    if (cmd.type == NICK && cmd.rest != NULL)
    {
        if (!find_name(user, cmd.rest))
        {
            strncpy(user[fd]->name, cmd.rest, 12);
            user[fd]->status = FD_CLIENT;
        }
        else
            write_buf(&(user[fd]->snd_buf),
                    "Init error: nickname already in use\n", 36);
    }
    else
        write_buf(&(user[fd]->snd_buf),
                "Init error: need nickname (/nick NAME)\n", 39);
}
