NAME = libftprintf.a

HEADER_DIR = ./includes/
HEADER_NAME = ft_printf.h
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_NAME))

SRCDIR = ./srcs/
SRCS = start.c \
		pretreat_to_put.c \
		put.c \
		utils.c

OBJDIR = ./objs/
OBJS = $(SRCS:%.c=$(OBJDIR)%.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(HEADER_DIR)

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p objs

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJS) $(HEADER)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re