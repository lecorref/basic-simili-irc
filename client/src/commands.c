#include "client.h"

static void send_command(t_str_in *to_send, t_client *client, t_lst_head *chan)
{
    char    *c_name;

    to_send->str[to_send->size++] = '\n';
    if (to_send->str[0] == '/')
        write(client->sock, to_send->str, to_send->size);
    else
    {
        if (chan && chan->first)
        {
            c_name = ((t_channel *)chan->first->content)->name;
            if (c_name[0] == '#')
            {
                write(client->sock, c_name, strlen(c_name));
                write(client->sock, " ", 1);
            }
            else if (c_name[0] == '@')
            {
                write(client->sock, "/msg ", 5);
                write(client->sock, c_name + 1, strlen(c_name + 1));
                write(client->sock, " ", 1);
            }
            else
                beep();
        }
        write(client->sock, to_send->str, to_send->size);
    }
}

void        get_command(t_str_in *to_send, t_client *client, t_lst_head *chan)
{
    char    **tmp;

    if (!strncmp(to_send->str, "/connect ", 9))
    {
        tmp = ft_strsplit(to_send->str, ' ');
        if (init_client(client, tmp + 1))
        {
            beep();
            bzero(client, sizeof(t_client));
        }
        free_tab(tmp);
    }
    else if (FD_ISSET(client->sock, &client->fd_write))
        send_command(to_send, client, chan);
    bzero(to_send, sizeof(t_str_in));
}
