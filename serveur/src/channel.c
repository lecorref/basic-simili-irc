#include "ft_irc.h"

int     cmp_channel(void *channel, void *name)
{
    return !strcmp(((t_channel *)channel)->name, (char *)name);
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
    char        *name;
    t_channel   *chan;
    t_lst_elem  *client;

    if ((name = strsep(&(args.rest), " ")))
    {
        if (!(chan = lst_first_match(serv->chan_list, name, cmp_channel)))
            write_buf(&(user[fd]->snd_buf),
                    "Error: This channel doesn't exist\n", 35);
        else if (!(client = lst_match_elem(chan->user_list,
                        user[fd]->name, cmp_user)))
            write_buf(&(user[fd]->snd_buf),
                    "Error: You are not in this channel\n", 36);
        else
        {
            lst_remove(chan->user_list, client);
            chan->number--;
            send_channel(chan, "left this channel", user, fd);
        }
    }
}

void    find_channel(t_server *serv, t_cmd args, t_member **user, int fd)
{
    t_channel       *join;
    char            *name;

    if ((name = strsep(&(args.rest), " ")))
    {
        if (name[0] != '#')
            write_buf(&(user[fd]->snd_buf),
                    "Error: Channel name have to start with #\n", 42);

        else if (!(join = lst_first_match(serv->chan_list, name, cmp_channel)))
        {
            if (!(join = init_channel(name, user[fd])))
                write_buf(&(user[fd]->snd_buf),
                        "Error: Cannot create this channel\n", 35);
            else
                lst_pushfront(serv->chan_list, lst_create_no_malloc(join));
        }
        else
            join_channel(join, user[fd]);
    }
}
