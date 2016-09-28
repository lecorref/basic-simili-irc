#include "ft_irc.h"

int     ft_read(t_server *serv, t_member **user, int fd)
{
    int     ret;
    char    buf[READ_MAX];

    (void)serv;
    ret = READ_MAX;
    while (ret == READ_MAX)
    {
        bzero(buf, READ_MAX);
        if ((ret = read(fd, buf, READ_MAX)) <= 0)
        {
            close_client(user[fd], fd);
            bzero(user[fd], sizeof(t_member));
            return (1);
        }
        write_buf(&(user[fd]->rcv_buf), buf, ret);
    }
    return (0);
}
