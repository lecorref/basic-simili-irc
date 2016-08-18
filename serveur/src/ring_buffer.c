#include "ft_irc.h"

int         init_buffer(t_ring_buf *rbuf, int type)
{
    rbuf->size = (type == SEND) ? SEND_SIZE : RECEIVE_SIZE;
    if (!(rbuf->start = malloc(sizeof(char) * rbuf->size)))
        return (1);
    bzero(rbuf->start, rbuf->size);
    rbuf->end = rbuf->start + rbuf->size;
    rbuf->read = rbuf->start;
    rbuf->write = rbuf->start;
    rbuf->flag = 0;
    return (0);
}

int         write_buf(t_ring_buf *buf, char *str, int len)
{
    int     len2; //chose a better name

    if (buf->write > buf->read || (buf->write == buf->read && buf->flag == 0))
    {
        buf->flag = 1;
        if (buf->write + len < buf->end)
        {
            strncpy(buf->write, str, len);
            buf->write += len;
        }
        else
        {
            len2 = buf->end - buf->write;
            strncpy(buf->write, str, len);
            buf->write = buf->start;
            return (write_buf(buf, str + len2, len - len2));
        }
    }
    else
    {
        if (buf->write + len < buf->read)
        {
            strncpy(buf->write, str, len);
            buf->write += len;
        }
        else
        {
            strncpy(buf->write, str, (buf->read - buf->write));
            buf->write = buf->read;
            return (1);
        }
    }
    return (0);
}
