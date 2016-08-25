#include "ft_irc.h"

const char  *cmd_list[] = {"nick", "quit"};

void    parse_cmd(char *line, t_cmd *cmd)
{
    int     i;

    i = -1;
    if (line[0] != '/')
        return ;
    cmd->args = ft_strsplit(line + 1, ' ');
    while (++i < 2)
    {
        if (!strncmp(cmd->args[0], cmd_list[i], strlen(cmd_list[i])))
            cmd->type = i;
    }
    if (cmd->type < 0)
        cmd->type = -2;
}

void    get_client_name(t_member **user, int fd)
{
    char        *str;

    if (!(str = read_buf(&(user[fd]->rcv_buf))))
        return ;
    if (strncmp("/nick", str, 5))
    {

    }
    else
        printf("nick\n");
    free(str);
}

void    get_commands(t_server *serv, t_member **user, int fd)
{
    char        *str;
    t_cmd       args;

    ft_read(serv, user, fd);
    if (!(str = read_buf(&(user[fd]->rcv_buf))))
        return ;
    bzero(&args, sizeof(t_cmd));
    args.type = -1;
    parse_cmd(str, &args);
    if (user[fd]->status == FD_UNAMED_CLIENT)
        get_client_name(user, fd);
    else
        send_msg(serv, user, fd);
}
