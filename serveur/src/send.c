#include "ft_irc.h"

void    compose_message(t_ring_buf *buf, char name[12], char *cpy)
{
    write_buf(buf, name, 12);
    write_buf(buf, ": ", 2);
    write_buf(buf, cpy, strlen(cpy));
    write_buf(buf, "\n", 1);
}

void    send_msg(t_server *serv, t_member **user, char *str, int fd)
{
    int     i;

    i = 2;
    while (++i <= (int)serv->fd_max)
    {
        if (user[i]->status == FD_CLIENT)
            compose_message(&(user[i]->snd_buf), user[fd]->name, str);
    }
}
