SRCS_DIR = srcs/

SRCS=	minishell.c \
		lexer.c \
		chevrons.c \
		parser.c \
		commands.c \
		tokenize.c \
		interpreter.c \
		translation.c \
		cuts.c \
		chunks.c \
		utils.c \

OBJ_DIR = objs/

OBJS = ${SRCS:%.c=${OBJ_DIR}%.o}

LIBFT_PATH = libft

NAME= minishell

CC= gcc

FLAGS= -Wall -Wextra -Werror

LEAKS= -g3 -fsanitize=address

INC_DIR = incs

INCLUDES =	${INC_DIR}/parsing.h \
			${INC_DIR}/mini.h \
			${INC_DIR}/lib.h \

${OBJ_DIR}%.o : ${SRCS_DIR}%.c	${INCLUDES}
				mkdir -p objs
				${CC} ${FLAGS} -c $< -o $@ -I.

all: makelib ${NAME}

${NAME}:	Makefile ${OBJS}
			${CC} ${FLAGS} ${OBJS} ${LEAKS} -lreadline ${LIBFT_PATH}/libft.a -o ${NAME}

makelib:
		${MAKE} -C ${LIBFT_PATH}/ bonus

clean:
			${MAKE} -C ${LIBFT_PATH}/ fclean
			rm -f ${OBJS}
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

PHONY= all clean fclean re