#include "linked_list.h"

void    rotate_left(t_lst_head *head)
{
    t_lst_elem  *elem;

    if (!head || !head->last)
        return ;
    elem = head->last;
    if (!elem->prev)
        return ;
    head->last = elem->prev;
    (elem->prev)->next = NULL;
    elem->prev = NULL;
    (head->first)->prev = elem;
    elem->next = head->first;
    head->first = elem;
}

void    rotate_right(t_lst_head *head)
{
    t_lst_elem  *elem;

    if (!head || !head->first)
        return ;
    elem = head->first;
    if ( !elem->next)
        return ;
    head->first = elem->next;
    (elem->next)->prev = NULL;
    elem->next = NULL;
    (head->last)->next = elem;
    elem->prev = head->last;
    head->last = elem;
}
