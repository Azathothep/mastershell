/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/24 13:13:53 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static int	isempty(char *line)
{
	return (!ft_strncmp(line, "", 1));
}

static void	display(char ***commands)
{
	int	i;
	int	j;

	i = -1;
	while (commands[++i])
	{
		j = -1;
		while (commands[i][++j])
			printf("%s$\n", commands[i][j]);
		printf("\n");
	}
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
	mini.parse_error = 0;
	return (mini);
}

static void	launch_shell(char **envp)
{
	t_mini	mini;
	t_list	*begin_lexicon;
	char	*buffer;

	mini = init_mini(envp);
	while (1)
	{
		buffer = readline("-> mastershell #> ");
		if (!isempty(buffer))
		{
			add_history(buffer);
			begin_lexicon = lexer(buffer, &mini);
			free(buffer);
			if (!begin_lexicon)
				return ;
			mini = parser(&begin_lexicon, mini);
			ft_lstclear(&begin_lexicon, &lst_del);
			if (!mini.parse_error)
				display(mini.commands); //line to delete
			printf("heredoc: %s\n", get_token(mini.heredocs[0]));
			free_cmd(mini.commands);
			mini.parse_error = 0;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	argc += 0;
	argv += 0;
	launch_shell(envp);
	return (0);
}
