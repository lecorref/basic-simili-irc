#include "ft_irc.h"

void    remove_from_chan(t_lst_head *chan, t_member *user)
{
    t_lst_elem  *elem;

    elem = chan->first;
    while (elem)
    {
        lst_free_match(((t_channel *)elem->content)->user_list,
                user->name, cmp_user, free_client);
        elem = elem->next;
    }
}

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
            remove_from_chan(serv->chan_list, user[fd]);
            close_client(user[fd], fd);
            bzero(user[fd], sizeof(t_member));
            return (1);
        }
        write_buf(&(user[fd]->rcv_buf), buf, ret);
    }
    return (0);
}
