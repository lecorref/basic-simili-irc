#include "ft_irc.h"

const char  *cmd_list[] = {"/nick", "/msg", "/join", "/leave"};

void    parse_cmd(char *line, t_cmd *cmd)
{
    int     i;

    i = -1;
    if (line[0] != '/')
        return ;
    cmd->first = strsep(&line, " ");
    cmd->rest = line;
    while (++i < 4)
    {
        if (!strncmp(cmd->first, cmd_list[i], strlen(cmd_list[i])))
            cmd->type = i;
    }
    if (cmd->type < 0)
        cmd->type = -2;
}

void    dispatch_cmd(t_server *serv, t_cmd args, t_member **user, int fd)
{
    t_fpointer cmd_pointer[4] = {
        get_client_name, send_msg, find_channel, leave_channel};

    cmd_pointer[args.type](serv, args, user, fd);
}

void    get_commands(t_server *serv, t_member **user, int fd)
{
    char        *str;
    t_cmd       args;
    char        *tmp;

    ft_read(serv, user, fd);
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
            send_all(serv, user, str, fd);
        else if (args.type >= 0)
            dispatch_cmd(serv, args, user, fd);
    }
    free(str);
}
