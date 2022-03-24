/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/24 16:47:41 by fbelthoi         ###   ########.fr       */
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

static void	display(t_mini *mini)
{
	int		i;
	int		j;
	t_list	*lst;
	char	***commands;

	commands = mini->commands;
	i = -1;
	while (commands[++i])
	{
		j = -1;
		while (commands[i][++j])
			printf("%s ", commands[i][j]);
		printf("|| heredocs : ");
		lst = mini->heredocs[i];
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("|| infiles : ");
		lst = mini->infile[i].files;
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("|| outfiles : ");
		lst = mini->outfile[i].files;
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("\n");
	}
	printf("\n");
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
			parser(&begin_lexicon, &mini);
			ft_lstclear(&begin_lexicon, &lst_del);
			if (!mini.parse_error)
				display(&mini); //line to delete
			free_cmd(mini.commands);
			mini.parse_error = 0;
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
	launch_shell(envp);
	return (0);
}
