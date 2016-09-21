# binaries
CC		= /usr/bin/clang
RM		= /bin/rm
MAKE	= /usr/bin/make
MKDIR	= /bin/mkdir

# app name
NAME	= client

# dir
ROOT	= $(shell pwd)
OBJDIR	= $(ROOT)/obj
SRCDIR	= $(ROOT)/src
INCDIR	= $(ROOT)/include
LIBDIR	= $(ROOT)/../lib
LFTINC	= $(LIBDIR)/include

# compil flags
CFLAGS	= -I $(INCDIR) -I $(LFTINC) -Wall -Wextra -Werror
LIBS = -L $(LIBDIR) -llinked_list -lncurses

# source files
SRC		= \
		  error.c \
		  init.c \
		  loop.c \
		  main.c

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

