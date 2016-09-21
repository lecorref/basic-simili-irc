#include "client.h"

int         g_continue = 1;

void        int_handler(int dummy)
{
    (void)dummy;
    g_continue = 0;
}

static void init_select(t_client *client)
{
    FD_ZERO(&client->fd_read);
    if (client->port)
        FD_SET(client->sock, &client->fd_read);
    FD_SET(STDIN_FILENO, &client->fd_read);
}

static int  ft_select(t_client *client)
{
    struct timeval  time;

    time.tv_sec = 0;
    time.tv_usec = 0;
    if (client->port)
        return (select(client->sock + 1, &client->fd_read, NULL, NULL, &time));
    return (select(STDIN_FILENO + 1, &client->fd_read, NULL, NULL, &time));
}

void        main_loop(t_client *client)
{
    while (g_continue)
    {
        signal(SIGINT, int_handler);
        init_select(client);
        ft_select(client);
        if (client->port && FD_ISSET(client->sock, &client->fd_read))
            ; //receive message from server
        if (FD_ISSET(STDIN_FILENO, &client->fd_read))
            ;//read message rom input
    }
}


