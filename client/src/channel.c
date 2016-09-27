#include "client.h"

int     cmp_chan(void *chan, void *str)
{
    return (!strcmp(((t_channel *)chan)->name, str));
}

void    right_chan(t_lst_head *chan, t_term *term)
{
    rotate_right(chan);
    wclear(term->output_win);
    wclear(term->input_win);
    box(term->input_win, 0, 0);
    input_win(term, "", 0, chan);
    print_window(term->output_win, chan);
}

void    left_chan(t_lst_head *chan, t_term *term)
{
    rotate_left(chan);
    wclear(term->output_win);
    wclear(term->input_win);
    box(term->input_win, 0, 0);
    input_win(term, "", 0, chan);
    print_window(term->output_win, chan);
}

void    free_chan(void *content)
{
    t_channel   *chan;

    chan = content;
    free(chan->name);
    lst_delete(chan->msg, free);
    free(chan->msg);
    free(chan);
}
