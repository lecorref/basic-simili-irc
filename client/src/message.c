#include "client.h"

static char *join(char *str, char *buf)
{
    char    *ret;

    ret = ft_strjoin(str, buf);
    if (str != NULL)
        free(str);
    return (ret);
}

static int  put_in_chan(t_lst_head *chan, char *message)
{
    char            *name;
    char            *str;
    t_channel       *content;
    t_lst_elem      *elem;

    while ((str = strsep(&message, "\n")) && strlen(str))
    {
        name = strsep(&str, " ");
        if ((content = lst_first_match(chan, name, cmp_chan)))
        {
            lst_pushback(content->msg, lst_create_no_malloc(strdup(str)));
            if (content->msg->size > 200)
            {
                elem = lst_pop(content->msg, 0);
                lst_delete_elem(&elem, free);
            }
        }
        else
        {
            if (!(content = malloc(sizeof(t_channel))))
                return (0);
            content->name = strdup(name);
            content->msg = lst_init(lst_create_no_malloc(strdup(str)));
            lst_pushback(chan, lst_create_no_malloc(content));
            return (1);
        }
    }
    return (0);
}

static int  ft_read(t_client *client, t_lst_head *chans)
{
    int     ret;
    char    buf[READ_MAX];
    char    *tmp;

    ret = READ_MAX;
    tmp = NULL;
    while (ret == READ_MAX)
    {
        bzero(buf, READ_MAX);
        if ((ret = read(client->sock, buf, READ_MAX)) <= 0)
            return (-1);
        tmp = join(tmp, buf);
    }
    ret = put_in_chan(chans, tmp);
    free(tmp);
    return (ret);
}

int         get_message(t_term *term, t_client *client,
                            t_lst_head *chans, t_str_in input)
{
    int     ret;

    ret = ft_read(client, chans);
    print_window(term->output_win, chans);
    input_win(term, input.str, input.pos, chans);
    return (ret);
}

