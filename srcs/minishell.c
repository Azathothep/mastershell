/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:30:48 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../incs/parsing.h"

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
			printf("%s ", commands[i][j]);
		printf("\n");
	}
}

static void	launch_shell(void)
{
	char	*buffer;
	char	**lexicon;
	char	***commands;

	while (1)
	{
		buffer = readline("-> mastershell #> ");
		if (!buffer)
			return ;
		if (!isempty(buffer))
		{
			add_history(buffer);
			lexicon = lexer(buffer);
			free(buffer);
			if (!lexicon)
				return ;
			commands = parser(lexicon);
			free_lexicon(lexicon);
			display(commands); //line to delete
			free_cmd(commands);
		}
	}
}

int	main(void)
{
	launch_shell();
	return (0);
}
