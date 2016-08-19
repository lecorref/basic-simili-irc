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

static int  copy_buf(char *dest, char *src, int len)
{
    strncpy(dest, src, len);
    return (len);
}

int         write_buf(t_ring_buf *buf, char *str, int len)
{
    int     len2; //chose a better name

    if (buf->write > buf->read || (buf->write == buf->read && buf->flag == 0))
    {
        buf->flag = 1;
        if (buf->write + len < buf->end)
            buf->write += copy_buf(buf->write, str, len);
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

static char get_last_char(t_ring_buf *buf)
{
    return (buf->write == buf->start ? *(buf->end) : *(buf->write - 1));
}

char        *read_buf(t_ring_buf *buf)
{
    char        *ret;
    int         len;
    int         len2;

    ret = NULL;
    if (buf->flag == 0 || get_last_char(buf) != '\n')
        return (ret);
    len = buf->write - buf->read;
    if (len > 0)
        ret = strndup(buf->read, len);
    else
    {
        len = buf->end - buf->read;
        len2 = buf->write - buf->start;
        if (!(ret = malloc(sizeof(char) * (len + len2) + 1)))
            return (NULL);
        bzero(ret, len + len2 + 1);
        ret = strncpy(ret, buf->read, len);
        ret = strncat(ret, buf->start, len2);
    }
    buf->flag = 0;
    buf->read = buf->write;
    return (ret);
}
