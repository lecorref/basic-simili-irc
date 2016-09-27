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
    FD_ZERO(&client->fd_write);
    if (client->port)
    {
        FD_SET(client->sock, &client->fd_read);
        FD_SET(client->sock, &client->fd_write);
    }
}

static int  ft_select(t_client *client)
{
    struct timeval  time;

    time.tv_sec = 0;
    time.tv_usec = 0;
    if (client->port)
        return (select(client->sock + 1, &client->fd_read,
                    &client->fd_write, NULL, &time));
    return (0);
}

void        main_loop(t_client *client, t_lst_head *chan)
{
    t_str_in        input;
    t_term          term;
    int             select;

    bzero(&input, sizeof(input));
    init_ncurse(&term);
    while (g_continue)
    {
        signal(SIGINT, int_handler);
        usleep(10);
        init_select(client);
        select = ft_select(client);
        if (select && FD_ISSET(client->sock, &client->fd_read))
        {
            if (get_message(&term, client, chan, input) < 0)
                g_continue = 0;
        }
        if ((input.c = getch()) > 0)
        {
            get_input(&input, &term, client, chan);
            input_win(&term, input.str, input.pos, chan);
        }
    }
    lst_delete(chan, free_chan);
    endwin();
}


