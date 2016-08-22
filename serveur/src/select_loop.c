#include <signal.h>
#include "ft_irc.h"

int g_continue = 1;

void    int_handler(int dummy)
{
    (void)dummy;
    g_continue = 0;
}

void    init_select(t_server *serv, t_member **user)
{
    unsigned int     i;

    i = 3;
    FD_ZERO(&serv->fd_read);
    FD_ZERO(&serv->fd_write);
    while (i <= serv->fd_max)
    {
        if (user[i]->status != FD_FREE)
        {
            FD_SET(i, &serv->fd_read);
            if (user[i]->status != FD_SERVER)
                FD_SET(i, &serv->fd_write);
        }
        i++;
    }
}

void    ft_select(t_server *serv)
{
    struct timeval  time;

    time.tv_sec = 0;
    time.tv_usec = 0;
    serv->fd_select = select(serv->fd_max + 1, &serv->fd_read,
            &serv->fd_write, NULL, &time);
}

void    process_select(t_server *serv, t_member **user)
{
    unsigned int      i;

    i = 3;
    while (i <= serv->fd_max && serv->fd_select)
    {
        if (FD_ISSET(i, &serv->fd_read))
        {
            if (user[i]->status == FD_SERVER)
                ft_accept(serv, user);
            else
                ft_read(serv, user[i], i);
        }
        if (FD_ISSET(i, &serv->fd_write))
            ft_write(&(user[i]->snd_buf), i);
        if ((FD_ISSET(i, &serv->fd_read)) || (FD_ISSET(i, &serv->fd_write)))
            serv->fd_select--;
        i++;
    }
}

void    loop(t_server *serv, t_member **user)
{
    while (g_continue)
    {
        signal(SIGINT, int_handler);
        init_select(serv, user);
        ft_select(serv);
        process_select(serv, user);
    }
}
