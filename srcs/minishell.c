/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/29 16:39:58 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"
#include "../incs/pipe.h"

static int	errno_ok(void)
{
	if (errno == 1)
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
	mini.cmdenv = NULL;
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
		buffer = readline("-> mastershell #> ");
		if (!isempty(buffer))
		{
			add_history(buffer);
			begin_lexicon = lexer(buffer, &mini);
			free (buffer);
			if (begin_lexicon)
				if (parser(&begin_lexicon, &mini))
					ft_start_pipe(&mini);
			ft_lstclear(&begin_lexicon, &lst_del);
			free_mini(&mini);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	argv += 0;
	if (argc > 1)
	{
		printf("no arguments required\n");
		return (0);
	}
	errno = 0;
	launch_shell(envp);
	return (0);
}
