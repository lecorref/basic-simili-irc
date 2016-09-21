#include "client.h"

static int  init_connect(t_client *init, char *serv_addr)
{
    struct protoent     *proto;
    struct sockaddr_in  sin;

    bzero(&sin, sizeof(sin));
    if (!(proto = getprotobyname("tcp")))
        return (pr_error("tcp: Unsupported protocol"));
    if ((init->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (pr_error("Cannot create socket"));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(init->port);
    sin.sin_addr.s_addr = inet_addr(serv_addr);
    if (connect(init->sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
        return (pr_error("Cannot connect to server"));
    return (0);
}

int         init_client(t_client *init, char **args)
{
    if (!args[1])
        init->port = 6667;
    else
        init->port = atoi(args[1]);
    return (init_connect(init, args[0]));
}

