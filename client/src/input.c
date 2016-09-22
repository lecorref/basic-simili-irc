#include "client.h"

static void add_char(t_str_in *input, char c)
{
    int     pos;

    pos = input->pos;
    if (input->size < BUFF)
    {
        memmove(input->str + pos + 1, input->str + pos, input->size - pos);
        input->str[input->pos++] = c;
        input->size++;
    }
    else
        beep();
}

static void move_cursor(t_str_in *input, int dir)
{
    if ((input->pos * dir) < (dir == 1 ? input->size : 0))
        input->pos += dir;
    else
        beep();
}

static void backspace(t_str_in *input)
{
    int     pos;

    pos = input->pos;
    if (pos > 0)
    {
        memmove(input->str + pos - 1, input->str + pos, input->size - pos);
        input->pos--;
        input->size--;
    }
    else
        beep();
}

static void delete(t_str_in *input)
{
    int     pos;

    pos = input->pos;
    if (pos < input->size)
    {
        memmove(input->str + pos, input->str + pos + 1, input->size - pos - 1);
        input->size--;
    }
    else
        beep();
}

void        get_input(t_str_in *input, int c)
{
    if (c == KEY_ENTER || c == '\n' || c == '\r')
        ;//parse command
    else if (isprint(c))
        add_char(input, c);
    else if (c == KEY_LEFT)
        move_cursor(input, -1);
    else if (c == KEY_RIGHT)
        move_cursor(input, 1);
    else if (c == KEY_BACKSPACE)
        backspace(input);
    else if (c == KEY_DC)
        delete(input);
    else
        beep();
    input->str[input->size] = ' ';
}
/*
static void readline(char *buffer, int buflen)
{
  int old_curs = curs_set(1);
  int pos = 0;
  int len = 0;
  int x, y;

  getyx(stdscr, y, x);
  for (;;) {
    int c;

    buffer[len] = ' ';
    mvaddnstr(y, x, buffer, len+1);
    move(y, x+pos);
    c = getch();

    } else if (c == KEY_DC) {
      if (pos < len) {
        memmove(buffer+pos, buffer+pos+1, len-pos-1);
        len -= 1;
      } else {
        beep();
      }
    } else {
      beep();
    }
  }
  buffer[len] = '\0';
  if (old_curs != ERR) curs_set(old_curs);
}
*/
