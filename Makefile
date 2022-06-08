SRCS_DIR = srcs/

SRCS_DIR_PARSING = srcs/parsing/

SRCS_DIR_EXEC = srcs/pipe/

SRCS = minishell.c

SRCS_PARSING =	lexer.c \
		parser.c \
		tokenize.c \
		translation/heredoc.c \
		translation/translation.c \
		translation/chevrons.c \
		translation/chevrons_utils.c \
		utils/lst.c \
		utils/cuts.c \
		utils/chunks.c \
		utils/utils.c \
		utils/free.c \
		utils/signal.c \
		utils/termios.c \
		utils/cut_by_spaces.c \

SRCS_EXEC = builtin/builtin.c \
        builtin/builtinpipe.c \
        error/error.c \
        error/error2.c \
        utils/futils.c \
        utils/futils2.c \
        init/initpipex.c \
        init/initpipex2.c \
        init/initpipex3.c \
        pipe/pipe.c \
        pipe/pipe2.c \
        pipe/pipehere.c \
        pipe/pipehere2.c \
        builtin/unset.c \
        builtin/pwd.c \
        builtin/export.c \
        builtin/export2.c \
        builtin/exit.c \
        builtin/env.c \
        builtin/echo.c \
        builtin/cd.c \
        builtin/cd2.c \
        error/freeall.c \
        error/freeall2.c \
        utils/futilspipex.c \
        utils/futilspipex2.c \
        utils/futilspipex3.c \
        utils/futilspipehere.c \
		utils/exitstatus.c \
		init/initpipex4.c \

OBJ_DIR = objs/

OBJ_DIR_PARSING = ${OBJ_DIR}parsing/

OBJ_DIR_EXEC = ${OBJ_DIR}exec/

OBJS =	${SRCS:%.c=${OBJ_DIR}%.o} ${OBJS_PARSING} ${OBJS_EXEC}

OBJS_PARSING = ${SRCS_PARSING:%.c=${OBJ_DIR_PARSING}%.o}

OBJS_EXEC = ${SRCS_EXEC:%.c=${OBJ_DIR_EXEC}%.o}

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
				mkdir -p ${OBJ_DIR_PARSING}
				mkdir -p ${OBJ_DIR_PARSING}/translation
				mkdir -p ${OBJ_DIR_PARSING}/utils
				mkdir -p ${OBJ_DIR_EXEC}
				mkdir -p ${OBJ_DIR_EXEC}/builtin
				mkdir -p ${OBJ_DIR_EXEC}/error
				mkdir -p ${OBJ_DIR_EXEC}/init
				mkdir -p ${OBJ_DIR_EXEC}/pipe
				mkdir -p ${OBJ_DIR_EXEC}/utils
				${CC} ${FLAGS} -I$(shell brew --prefix readline)/include -c $< -o $@

all: makelib ${NAME}

${NAME}:	Makefile ${OBJS}
			${CC} ${FLAGS} ${OBJS} ${LIBFT_PATH}/libft.a -L$(shell brew --prefix readline)/lib -lreadline -o ${NAME}
makelib:
			${MAKE} -C ${LIBFT_PATH}/ all

clean:
			${MAKE} -C ${LIBFT_PATH}/ fclean
			rm -f ${OBJS}
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

PHONY= all clean fclean re