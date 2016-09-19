# binaries
CC		= /usr/bin/clang
RM		= /bin/rm
MAKE	= /usr/bin/make
MKDIR	= /bin/mkdir
AR		= /usr/bin/ar
RANLIB	= /usr/bin/ranlib

# app name
NAME	= liblinked_list.a

# dir
ROOT	= $(shell pwd)
OBJDIR	= $(ROOT)/obj
SRCDIR	= $(ROOT)/src
INCDIR	= $(ROOT)/include

# compil flags
CFLAGS	= -I $(INCDIR) -Wall -Wextra -Werror

# source files
SRC		= \
		  linked_list_1.c \
		  linked_list_2.c \
		  linked_list_3.c

# obj
OBJS	= $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling linked list library"
	@$(AR) -rc $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $< -o $@ -c $(CFLAGS)

$(OBJDIR):
	@$(MKDIR) $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
