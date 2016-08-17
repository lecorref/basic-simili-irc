#include "ft_irc.h"

int         init_buffer(t_ring_buf *rbuf, int type)
{
    rbuf->size = type == SEND ? SEND_SIZE : RECEIVE_SIZE;
    if (!(rbuf->buffer = malloc(sizeof(char) * rbuf->size)))
        return (1);
    rbuf->start = rbuf->buffer;
    rbuf->end = rbuf->buffer;
    return (0);
}
