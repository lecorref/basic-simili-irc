#include "client.h"

static void send_command(t_str_in *to_send, t_client *client)
{
    to_send->str[to_send->size++] = '\n';
    if (to_send->str[0] == '/')
        write(client->sock, to_send->str, to_send->size);
    else
    {
        //channel stuff when channel will be implemented
        write(client->sock, to_send->str, to_send->size);
    }
}

void        get_command(t_str_in *to_send, t_client *client)
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
        send_command(to_send, client);
    bzero(to_send, sizeof(t_str_in));
}
