#include "client.h"

int     ft_read(t_client *client)
{
    int     ret;
    char    buf[READ_MAX];

    ret = READ_MAX;
    while (ret == READ_MAX)
    {
        bzero(buf, READ_MAX);
        if ((ret = read(client->sock, buf, READ_MAX)) <= 0)
            return (-1); //close client
        printf("%s\n", buf); //put response in linked_list
    }
    return (ret);
}

int     get_message(t_term *term, t_client *client)
{
    ft_read(client);
    (void)term;
    //do stuff with the window
    return (0);
}

