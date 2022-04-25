/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/04/25 15:06:08 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"
#include "../incs/pipe.h"
#include <termios.h>

static int	errno_ok(void)
{
	if (errno == 1 || errno == 66)
		return (0);
	return (1);
}

static int	isempty(char *line)
{
	return (!ft_strncmp(line, "", 1));
}

static t_mini	init_mini(char **envp)
{
	t_mini	mini;

	mini.commands = NULL;
	mini.infile = NULL;
	mini.outfile = NULL;
	mini.errfile = NULL;
	mini.envpl = NULL;
	mini.nbc = 0;
	mini.pipex = NULL;
	mini.envp = envp;
	mini.exit_status = 0;
	mini.infile = NULL;
	mini.outfile = NULL;
	mini.heredocs = NULL;
	return (mini);
}

static void	launch_shell(char **envp)
{
	t_mini	mini;
	t_list	*begin_lexicon;
	char	*buffer;

	mini = init_mini(envp);
	while (errno_ok())
	{
		errno = 0;
		ft_init_signals_interactive();
		buffer = readline("-> mastershell #> ");
		if (!isempty(buffer))
		{
			add_history(buffer);
			begin_lexicon = lexer(buffer, &mini);
			ft_free (buffer);
			if (begin_lexicon)
				if (parser(&begin_lexicon, &mini) && ft_signal_default())
					ft_start_pipe(&mini);
			ft_lstclear(&begin_lexicon, &lst_del);
			free_mini(&mini);
		}
		if (!buffer)
			exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	termios_new;
	struct termios	termios_save;

	argv += 0;
	if (argc > 1)
	{
		printf("no arguments required\n");
		return (0);
	}
	errno = 0;
	tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
	launch_shell(envp);
	tcsetattr(0, 0, &termios_save);
	return (0);
}
