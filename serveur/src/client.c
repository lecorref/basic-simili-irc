#include "ft_irc.h"

int     find_name(t_member **user, char *name)
{
    int     i;

    i = 2;
    while (++i < FD_MAX)
    {
        if (user[i]->status == FD_CLIENT)
        {
            if (!strncmp(user[i]->name, name, 12))
                return (i);
        }
    }
    return (0);
}

int     cmp_user(void *user, void *name)
{
    return !strncmp(((t_member *)user)->name, (char *)name, 12);
}

void    change_name(t_member **user, char *new, t_lst_head *chan_list, int fd)
{
    t_lst_elem  *tmp;
    char        buff[43];

    bzero(buff, 43);
    snprintf(buff, 42, "%s is now known as %s", user[fd]->name, new);
    if (!chan_list || !chan_list->first)
        return ;
    tmp = chan_list->first;
    while (tmp)
    {
        if (lst_match_elem(((t_channel *)tmp->content)->user_list,
                    user[fd]->name, cmp_user))
            info_channel(tmp->content, buff);
        tmp = tmp->next;
    }
}

void    get_client_name(t_server *serv, t_cmd cmd, t_member **user, int fd)
{
    char    new_name[13];

    if (cmd.type == NICK && cmd.rest != NULL)
    {
        if (!find_name(user, cmd.rest))
        {
            bzero(new_name, 13);
            strncpy(new_name, cmd.rest, 12);
            change_name(user, new_name, serv->chan_list, fd);
            strncpy(user[fd]->name, cmd.rest, 12);
            user[fd]->status = FD_CLIENT;
            write_buf(&(user[fd]->snd_buf), "info new nickname\n", 19);
        }
        else
            write_buf(&(user[fd]->snd_buf),
                    "info Error: nickname already in use\n", 41);
    }
    else
        write_buf(&(user[fd]->snd_buf),
                "info Error: need nickname (/nick NAME)\n", 40);
}
