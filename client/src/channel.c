#include "client.h"

int     cmp_chan(void *chan, void *str)
{
    return (!strcmp(((t_channel *)chan)->name, str));
}

void    right_chan(t_lst_head *chan, t_term *term)
{
    t_lst_elem  *elem;

    if (!chan || !chan->first)
        return ;
    elem = chan->first;
    if ( !elem->next)
        return ;
    chan->first = elem->next;
    (elem->next)->prev = NULL;
    elem->next = NULL;
    (chan->last)->next = elem;
    elem->prev = chan->last;
    chan->last = elem;
    wclear(term->output_win);
    wclear(term->input_win);
    box(term->input_win, 0, 0);
    input_win(term, "", 0, chan);
    print_window(term->output_win, chan);
}

void    left_chan(t_lst_head *chan, t_term *term)
{
    t_lst_elem  *elem;

    if (!chan || !chan->last)
        return ;
    elem = chan->last;
    if (!elem->prev)
        return ;
    chan->last = elem->prev;
    (elem->prev)->next = NULL;
    elem->prev = NULL;
    (chan->first)->prev = elem;
    elem->next = chan->first;
    chan->first = elem;
    wclear(term->output_win);
    wclear(term->input_win);
    box(term->input_win, 0, 0);
    input_win(term, "", 0, chan);
    print_window(term->output_win, chan);
}
