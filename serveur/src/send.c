#include "ft_irc.h"

void    compose_message(t_ring_buf *buf, char name[12], char *cpy)
{
    /*
     * TODO: add channel name or user name in private discussions
     */
    write_buf(buf, name, 12);
    write_buf(buf, ": ", 2);
    write_buf(buf, cpy, strlen(cpy));
    write_buf(buf, "\n", 1);
}

void    send_all(t_server *serv, t_member **user, char *str, int fd)
{
    int     i;

    i = 2;
    while (++i <= (int)serv->fd_max)
    {
        if (user[i]->status == FD_CLIENT)
            compose_message(&(user[i]->snd_buf), user[fd]->name, str);
    }
}

void    send_msg(t_server *serv, t_cmd cmd, t_member **user, int fd)
{
    int     rcv_id;

    (void)serv;
    if ((rcv_id = find_name(user, strsep(&(cmd.rest), " "))))
    {
        compose_message(&(user[rcv_id]->snd_buf), user[fd]->name, cmd.rest);
        compose_message(&(user[fd]->snd_buf), user[fd]->name, cmd.rest);
    }
    else
        write_buf(&(user[fd]->snd_buf), "Error: user not found\n", 23);
}
