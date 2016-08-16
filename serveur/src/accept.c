#include "ft_irc.h"

int         ft_accept(t_server *serv, t_member *user)
{
    int                 new_user;
    struct sockaddr_in  new_sin;
    socklen_t           sin_len;

    sin_len = sizeof(new_sin);
    if ((new_user = accept(serv->sock,
                    (struct sockaddr *)&new_sin, &sin_len)) < 0)
        return (1);
    if (sin_len > serv->fd_max)
        serv->fd_max++;
    if (serv->fd_max > FD_MAX)
        ;//close new fd then exit and log bad entry
    user[new_user].status = FD_CLIENT;
    return (0);
}