#include "ft_irc.h"


void    ft_write(t_ring_buf *buf, int fd)
{
    int     len;

    if (!buf || buf->flag == 0)
        return ;
    len = buf->write - buf->read;
    if (len > 0)
        buf->read += write(fd, buf->read, len);
    else
    {
        len = buf->end - buf->read;
        buf->read += write(fd, buf->read, len);
        if (buf->end == buf->read)
        {
            buf->read = buf->start;
            ft_write(buf, fd);
        }
    }
    if (buf->read == buf->write)
        buf->flag = 0;
}

