#include "ft_irc.h"

void    compose_message(t_ring_buf *buf, int num_args, ...)
{
    int         i;
    va_list     ap;
    char        *tmp;

    i = 0;
    va_start(ap, num_args);
    while (i < num_args)
    {
        tmp = va_arg(ap, char *);
        if (tmp)
            write_buf(buf, tmp, strlen(tmp));
        i++;
    }
    va_end(ap);
    write_buf(buf, "\n", 1);
}

void    info_channel(t_channel *chan, char *str)
{
    t_lst_elem  *tmp;

    tmp = chan->user_list->first;
    while (tmp)
    {
        compose_message(&(((t_member *)tmp->content)->snd_buf), 3,
                chan->name, " ", str);
        tmp = tmp->next;
    }
}

void    send_channel(t_channel *chan, char *str, t_member **user, int fd)
{
    t_lst_elem  *tmp;

    tmp = chan->user_list->first;
    while (tmp)
    {
        compose_message(&(((t_member *)tmp->content)->snd_buf), 5,
                chan->name, " ", user[fd]->name, ": ", str);
        tmp = tmp->next;
    }
}

void    send_all(t_server *serv, t_cmd cmd, t_member **user, int fd)
{
    t_channel    *chan;

    if (!(chan = lst_first_match(serv->chan_list, cmd.first, cmp_channel)))
        write_buf(&(user[fd]->snd_buf),
                "info Error: This channel doesn't exist\n", 40);
    else if (!(lst_first_match(chan->user_list,
                    user[fd]->name, cmp_user)))
        write_buf(&(user[fd]->snd_buf),
                "info Error: You are not in this channel\n", 41);
    else
        send_channel(chan, cmd.rest, user, fd);
}

void    send_msg(t_server *serv, t_cmd cmd, t_member **user, int fd)
{
    int     rcv_id;

    (void)serv;
    if (cmd.rest)
    {
        if ((rcv_id = find_name(user, strsep(&(cmd.rest), " "))))
        {
            compose_message(&(user[rcv_id]->snd_buf), 6,
                    "@",  user[fd]->name, " ", user[fd]->name, ": ", cmd.rest);
            compose_message(&(user[fd]->snd_buf), 6,
                    "@",  user[rcv_id]->name , " ", user[fd]->name, ": ", cmd.rest);
        }
        else
            write_buf(&(user[fd]->snd_buf), "info Error: user not found\n", 28);
    }
}
