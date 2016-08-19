#include "ft_irc.h"

int     ft_read(t_server *serv, t_member *user, int fd)
{
    int     ret;
    char    buf[READ_MAX];
    char *tmp;

    (void)serv;
    ret = READ_MAX;
    while (ret == READ_MAX)
    {
        bzero(buf, READ_MAX);
        if ((ret = read(fd, buf, READ_MAX)) <= 0)
            return 1; //close client
        if (write_buf(&(user->rcv_buf), buf, ret))
            ;//log error?
    }
    tmp = read_buf(&(user->rcv_buf));
    if (tmp)
    {
        printf("%s", tmp);
        free(tmp);
    }
    return (0);
}
