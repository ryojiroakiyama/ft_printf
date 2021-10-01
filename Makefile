NAME = libftprintf.a

HEADER_DIR = ./includes
HEADER_NAME = ft_printf.h
HEADER = ${addprefix ${HEADER_DIR}/, ${HEADER_NAME}}

SRCS_DIR = ./srcs
SRCS_NAME = start.c \
			pretreat_to_put.c \
			put.c \
			utils.c
SRCS = ${addprefix ${SRCS_DIR}/, ${SRCS_NAME}}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I${HEADER_DIR}

RM = rm -f

OBJS = ${SRCS:.c=.o}

${NAME}: ${OBJS} ${HEADER}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
