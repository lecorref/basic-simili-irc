#include "ft_irc.h"

const char  *cmd_list[] = {"/nick", "/msg", "/join", "/leave", "/who"};

void    who(t_server *serv, t_cmd args, t_member **user, int fd)
{
    char        *name;
    t_channel   *chan;
    t_lst_elem  *tmp;

    if ((name = strsep(&(args.rest), " ")))
    {
        if (!(chan = lst_first_match(serv->chan_list, name, cmp_channel)))
            write_buf(&(user[fd]->snd_buf),
                    "info Error: This channel doesn't exist\n", 40);
        else if (!(lst_match_elem(chan->user_list,
                        user[fd]->name, cmp_user)))
            write_buf(&(user[fd]->snd_buf),
                    "info Error: You are not in this channel\n", 41);
        else
        {
            tmp = chan->user_list->first;
            write_buf(&(user[fd]->snd_buf),
                    "info friends on this channel:", 30);
            while (tmp)
            {
                write_buf(&(user[fd]->snd_buf), ((t_member *)tmp->content)->name,
                            strlen(((t_member *)tmp->content)->name));
                if (tmp->next)
                    write_buf(&(user[fd]->snd_buf), ", ", 2);
                tmp = tmp->next;
            }
            write_buf(&(user[fd]->snd_buf), "\n", 1);
        }
    }
}

void    parse_cmd(char *line, t_cmd *cmd)
{
    int     i;

    i = -1;
    cmd->first = strsep(&line, " ");
    cmd->rest = line;
    if (cmd->first[0] != '/')
    {
        if (cmd->first[0] != '#')
            cmd->type = -2;
        return ;
    }
    while (++i < 5)
    {
        if (!strncmp(cmd->first, cmd_list[i], strlen(cmd_list[i])))
            cmd->type = i;
    }
    if (cmd->type < 0)
        cmd->type = -2;
}

void    dispatch_cmd(t_server *serv, t_cmd args, t_member **user, int fd)
{
    t_fpointer cmd_pointer[5] = {
        get_client_name, send_msg, find_channel, leave_channel, who};

    cmd_pointer[args.type](serv, args, user, fd);
}

void    get_commands(t_server *serv, t_member **user, int fd)
{
    char        *str;
    t_cmd       args;
    char        *tmp;

    if (ft_read(serv, user, fd))
        return ;
    if (!(str = read_buf(&(user[fd]->rcv_buf))))
        return ;
    tmp = str;
    bzero(&args, sizeof(t_cmd));
    args.type = -1;
    parse_cmd(tmp, &args);
    if (user[fd]->status == FD_UNAMED_CLIENT)
        get_client_name(serv, args, user, fd);
    else
    {
        if (args.type == -1)
            send_all(serv, args, user, fd);
        else if (args.type >= 0)
            dispatch_cmd(serv, args, user, fd);
        else
            write_buf(&(user[fd]->snd_buf),
                    "info Error: invalid command\n", 29);
    }
    free(str);
}
