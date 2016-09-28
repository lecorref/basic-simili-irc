#include "ft_irc.h"

int         init_client(t_member *user)
{
    bzero(user, sizeof(t_member));
    if (init_buffer(&(user->rcv_buf), RECEIVE)
            || init_buffer(&(user->snd_buf), SEND))
        return (1);
    user->status = FD_UNAMED_CLIENT;
    return (0);
}

static int  to_many_client(t_server *serv, int fd)
{
    write(fd, "info Error: cannot accept any new connexion\n", 45);
    serv->fd_max++;
    close(fd);
    return (1);
}

int         ft_accept(t_server *serv, t_member **user)
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
        return (to_many_client(serv, new_user));
    init_client(user[new_user]);
    return (0);
}
