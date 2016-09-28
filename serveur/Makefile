# binaries
CC		= /usr/bin/clang
RM		= /bin/rm
MAKE	= /usr/bin/make
MKDIR	= /bin/mkdir

# app name
NAME	= serveur

# dir
ROOT	= $(shell pwd)
OBJDIR	= $(ROOT)/obj
SRCDIR	= $(ROOT)/src
INCDIR	= $(ROOT)/include
LIBDIR	= $(ROOT)/../lib
LFTINC	= $(LIBDIR)/include

# compil flags
CFLAGS	= -I $(INCDIR) -I $(LFTINC) -Wall -Wextra -Werror -g
LIBS = -L $(LIBDIR) -l linked_list

# source files
SRC		= \
		  accept.c \
		  channel.c \
		  client.c \
		  close.c \
		  error.c \
		  get_commands.c \
		  main.c \
		  read.c \
		  ring_buffer.c \
		  select_loop.c \
		  send.c \
		  strsplit.c \
		  write.c

# obj
OBJS	= $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBDIR)
	@echo "Compiling server..."
	@$(CC) $(OBJS) -o $@ $(LIBS) $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $< -o $@ -c $(CFLAGS)

$(OBJDIR):
	@$(MKDIR) $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
