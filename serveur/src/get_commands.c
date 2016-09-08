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

void    get_client_name(t_cmd cmd, t_member **user, int fd)
{
    if (cmd.type == NICK && cmd.args[1] != NULL)
    {
        if (is_name_used(user, cmd.args[1]))
        {
            strncpy(user[fd]->name, cmd.args[1], 12);
            user[fd]->status = FD_CLIENT;
        }
        else
            write_buf(&(user[fd]->snd_buf),
                    "Init error: nickname already in use\n", 36);
    }
    else
        write_buf(&(user[fd]->snd_buf),
                "Init error: need nickname (/nick NAME)\n", 39);
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
        get_client_name(args, user, fd);
    else
        send_msg(serv, user, str, fd);
    free(str); //TODO: free args if type != -1.
}
