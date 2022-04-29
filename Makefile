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
		signal.c \

SRCS2 = builtin.c \
        builtinpipe.c \
        error.c \
        error2.c \
        futils.c \
        futils2.c \
        initpipex.c \
        initpipex2.c \
        initpipex3.c \
        pipe.c \
        pipe2.c \
        debug.c \
        pipehere.c \
        pipehere2.c \
        unset.c \
        pwd.c \
        export.c \
        export2.c \
        exit.c \
        env.c \
        echo.c \
        cd.c \
        cd2.c \
		freeall.c \
		freeall2.c \
		futilspipex.c \
		futilspipex2.c \

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
				${CC} ${FLAGS} -I$(shell brew --prefix readline)/include -c $< -o $@

all: makelib ${NAME}

${NAME}:	Makefile ${OBJS} ${OBJS2}
			${CC} ${FLAGS} ${OBJS} ${OBJS2} ${LEAKS} ${LIBFT_PATH}/libft.a -L$(shell brew --prefix readline)/lib -lreadline -o ${NAME}
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