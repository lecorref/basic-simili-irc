#include "ft_irc.h"

void        free_client(void *nil)
{
    (void)nil;
}

void        close_client(t_member *user, int id)
{
    close(id);
    free(user->snd_buf.start);
    user->snd_buf.start = NULL;
    free(user->rcv_buf.start);
    user->rcv_buf.start = NULL;
    bzero(user, sizeof(t_member));
}

void        exit_server(t_server *serv, t_member **user)
{
    int     i;

    i = 0;
    close(serv->sock);
    while (i <= FD_MAX)
    {
        if (user[i]->status != FD_FREE)
            close_client(user[i], i);
        free(user[i]);
        i++;
    }
    free(user);
}
