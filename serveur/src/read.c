#include "ft_irc.h"

int     ft_read(t_server *serv, t_member *user, int fd)
{
    int     ret;
    char    *buf;

    (void)serv;
    (void)user;
    ret = READ_MAX;
    buf = malloc(sizeof(char) * READ_MAX);
    while (ret == READ_MAX)
    {
        bzero(buf, READ_MAX);
        if ((ret = read(fd, buf, READ_MAX)) <= 0)
            return 1; //close client
        printf("%s", buf);
    }
    return (0);
}
