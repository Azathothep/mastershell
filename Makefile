SRCS_DIR = srcs/

SRCS_DIR2 = srcs/pipe/

SRCS=	minishell.c \
		lexer.c \
		heredoc.c \
		parser.c \
		tokenize.c \
		translation.c \
		chevrons.c \
		chevrons_utils.c \
		lst.c \
		cuts.c \
		chunks.c \
		utils.c \
		free.c \
		display.c \

SRCS2 = builtin.c \
        builtin2.c \
        error.c \
        futils.c \
        initpipex.c \
        initpipex2.c \
        initpipex3.c \
        pipe.c \
        pipe2.c \
        debug.c \

OBJ_DIR = objs/

OBJ_DIR2 = objs/pipe/

OBJS = ${SRCS:%.c=${OBJ_DIR}%.o}

OBJS2 = ${SRCS2:%.c=${OBJ_DIR2}%.o}

LIBFT_PATH = libft

NAME= minishell

CC= gcc

FLAGS= -Wall -Wextra -Werror

LEAKS= -g3 -fsanitize=address

INC_DIR = incs

INCLUDES =	${INC_DIR}/parsing.h \
			${INC_DIR}/mini.h \
			${INC_DIR}/lib.h \
			 ${INC_DIR}/pipe.h \

${OBJ_DIR}%.o : ${SRCS_DIR}%.c	${INCLUDES}
				mkdir -p objs
				mkdir -p objs/pipe
				${CC} ${FLAGS} -c $< -o $@ -I.

all: makelib ${NAME}

${NAME}:	Makefile ${OBJS} ${OBJS2}
			${CC} ${FLAGS} ${OBJS} ${OBJS2} -lreadline ${LIBFT_PATH}/libft.a -o ${NAME}

makelib:
			${MAKE} -C ${LIBFT_PATH}/ all

clean:
			${MAKE} -C ${LIBFT_PATH}/ fclean
			rm -f ${OBJS} ${OBJS2}
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

PHONY= all clean fclean re