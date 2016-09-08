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
            buf->write = stpncpy(buf->write, str, len);
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
        buf->flag = 1;
        if (buf->write + len < buf->read)
            buf->write = stpncpy(buf->write, str, len);
        else
        {
            buf->write = stpncpy(buf->write, str, (buf->read - buf->write));
            *(buf->write - 1) = '\n';
            return (1);
        }
    }
    return (0);
}

char        get_last_char(t_ring_buf *buf)
{
    return (buf->write == buf->start ? *(buf->end) : *(buf->write - 1));
}

/*
 * The -1 is to avoid copying the \n (as i will change it to \r\n)
 */
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
        ret = strndup(buf->read, (len - 1));
    else
    {
        len = buf->end - buf->read;
        len2 = buf->write - buf->start;
        if (!(ret = malloc(sizeof(char) * (len + len2))))
            return (NULL);
        bzero(ret, len + len2);
        ret = strncpy(ret, buf->read, len);
        ret = strncat(ret, buf->start, len2 - 1);
    }
    buf->flag = 0;
    buf->read = buf->write;
    return (ret);
}
