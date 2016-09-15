#include "ft_irc.h"

int     cmp_channel(void *channel, void *name)
{
    return strcmp(((t_channel *)channel)->name, (char *)name);
}

void    *init_channel(char *name, void *member)
{
    t_channel   *new;

    if (!(new = (t_channel *)malloc(sizeof(t_channel))))
        return (NULL);
    new->user_list = lst_init(lst_create_no_malloc(member));
    new->number = 1;
    new->name = strdup(name);
    return (new);
}

void    join_channel(t_channel *chan, void *user)
{
    if (!(lst_first_match(chan->user_list,
                    ((t_member *)user)->name, cmp_user)))
    {
        chan->number++;
        lst_pushfront(chan->user_list, lst_create_no_malloc(user));
    }
}

void    leave_channel(t_server *serv, t_cmd args, t_member **user, int fd)
{
    (void)serv;
    (void)args;
    (void)user;
    (void)fd;
}

void    find_channel(t_server *serv, t_cmd args, t_member **user, int fd)
{
    t_channel       *join;
    char            *name;

    name = strsep(&(args.rest), " ");
    if (!(join = lst_first_match(serv->chan_list, name, cmp_channel)))
    {
        if (!(join = init_channel(name, user[fd])))
            ; //error message
        else
            lst_pushfront(serv->chan_list, lst_create_no_malloc(join));
    }
    else
        join_channel(join, user[fd]);
}
