NAME = libftprintf.a

SRCS = ./input.c ./pretreat_to_put.c ./put.c ./utils.c

HEADER = ft_printf.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

OBJS = ${SRCS:.c=.o}

%.o: %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS} ${B_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
