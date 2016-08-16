#include "ft_irc.h"

int     get_port(char *number, int *port)
{
    if ((*port = atoi(number)) <= 0)
        return (1);
    return (0);
}

int     init(t_server *serv, t_member **user, int port)
{
    struct protoent     *proto;
    struct sockaddr_in  sin;

    bzero(serv, sizeof(t_server));
    serv->port = port;
    if (!(proto = getprotobyname("tcp")))
        return (r_error("tcp: Unsupported protocol\n"));
    serv->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(serv->port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serv->sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        dprintf(2, "Bind error on port %d\n", serv->port);
        return (1);
    }
    listen(serv->sock, FD_MAX);
    user[serv->sock]->status = FD_SERVER;
    serv->fd_max = serv->sock;
    return (0);
}

int     main(int ac, char **av)
{
    int         port;
    t_server    serv;
    t_member    **user;
    int         i;

    i = 0;
    user = malloc(sizeof(t_member *) * FD_MAX);
    while (i <= FD_MAX)
    {
        user[i] = malloc(sizeof(t_member));
        bzero(user[i], sizeof(t_member)); //use memalloc
        i++;
    }
    if (ac != 2)
    {
        usage(av[0]);
        return (1);
    }
    if (get_port(av[1], &port) || init(&serv, user, port))
        return (1);
    loop(&serv, user);
    return (0);
}

