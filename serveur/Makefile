# binaries
CC		= /usr/bin/clang
RM		= /bin/rm
MAKE	= /usr/bin/make
MKDIR	= /bin/mkdir

# app name
NAME	= ft_irc

# dir
ROOT	= $(shell pwd)
OBJDIR	= $(ROOT)/obj
SRCDIR	= $(ROOT)/src
INCDIR	= $(ROOT)/include

# compil flags
CFLAGS	= -I $(INCDIR) -Wall -Wextra -Werror

# source files
SRC		= \
		  error.c \
		  main.c

# obj
OBJS	= $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling server..."
	@$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $< -o $@ -c $(CFLAGS)

$(OBJDIR):
	@$(MKDIR) $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
