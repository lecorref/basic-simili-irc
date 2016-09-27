#include "client.h"

static char *join(char *str, char *buf)
{
    char    *ret;

    ret = ft_strjoin(str, buf);
    if (str != NULL)
        free(str);
    return (ret);
}

static int  put_in_chan(t_lst_head *chan, char *str)
{
    char            *name;
    t_channel       *content;

    name = strsep(&str, " ");
    if ((content = lst_first_match(chan, name, cmp_chan)))
        lst_pushback(content->msg, lst_create(str, strlen(str))); //del mess > 500
    else
    {
        if (!(content = malloc(sizeof(t_channel))))
            return (0);
        content->name = strdup(name);
        content->msg = lst_init(lst_create(str, strlen(str)));
        if (chan == NULL)
            chan = lst_init(lst_create_no_malloc(content));
        else
            lst_pushback(chan, lst_create_no_malloc(content));
        return (1);
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

