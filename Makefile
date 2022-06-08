SRCS_DIR = srcs/

SRCS_DIR_PARSING = srcs/parsing/

SRCS_DIR_EXEC = srcs/pipe/

SRCS_PARSING =	minishell.c \
		lexer.c \
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
		display.c \
		utils/signal.c \
		utils/termios.c \
		utils/cut_by_spaces.c \

SRCS_EXEC = builtin.c \
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
        futilspipex3.c \
        futilspipehere.c \
		exitstatus.c \
		initpipex4.c \

OBJ_DIR = objs/

OBJ_DIR_PARSING = ${OBJ_DIR}parsing/

OBJ_DIR_EXEC = ${OBJ_DIR}pipe/

OBJS =	${OBJS_PARSING} ${OBJS_EXEC}

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