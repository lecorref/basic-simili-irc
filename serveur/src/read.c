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
            return 1; //close client
        if (write_buf(&(user[fd]->rcv_buf), buf, ret))
            ;//log error?
    }
    return (0);
}
