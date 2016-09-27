#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>

typedef struct  s_lst_elem
{
    void                *content;
    struct s_lst_elem   *next;
    struct s_lst_elem   *prev;
}               t_lst_elem;

typedef struct  s_lst_head
{
    t_lst_elem          *first;
    t_lst_elem          *last;
    size_t              size;
}               t_lst_head;

t_lst_head      *lst_init(t_lst_elem *first);
t_lst_elem      *lst_create(void *content, size_t content_size);
t_lst_elem      *lst_create_no_malloc(void *content);
void            lst_pushfront(t_lst_head *head, t_lst_elem *new);
void            lst_pushback(t_lst_head *head, t_lst_elem *new);
t_lst_elem      *lst_pop(t_lst_head *head, unsigned int index_to_remove);
t_lst_elem      *lst_remove(t_lst_head *head, t_lst_elem *elem_to_remove);
void            lst_delete_elem(t_lst_elem **elem, void (*del)(void*));
void            lst_free_match(t_lst_head *hd, void *dt \
                            , int (*cmp)(void*, void*), void (*del)(void*));
void            lst_delete(t_lst_head *head, void (*del)(void *));
void            lst_insert(t_lst_head *head, t_lst_elem *new \
                            , int (*f)(void*, void*));
void            lst_insert_end(t_lst_head *head, t_lst_elem *new \
                            , int (*f)(void*, void*));
void            *lst_first_match(t_lst_head *hd, void *dt \
                            , int (*cmp)(void*, void*));
t_lst_elem      *lst_match_elem(t_lst_head *hd, void *dt, \
                                int (*cmp)(void*, void*));
void            rotate_left(t_lst_head *head);
void            rotate_right(t_lst_head *head);

#endif
