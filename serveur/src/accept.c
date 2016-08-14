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
    printf("new connection!\n");
    (void)user;

    return (0);
}
