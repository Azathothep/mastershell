/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/16 11:15:14 by marvin           ###   ########.fr       */
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
			printf("%s ", commands[i][j]);
		printf("\n");
	}
}

static void	launch_shell(void)
{
	t_mini	mini;
	t_list	*begin_lexicon;
	char	*buffer;

	while (1)
	{
		buffer = readline("-> mastershell #> ");
		if (!buffer)
			return ;
		if (!isempty(buffer))
		{
			add_history(buffer);
			begin_lexicon = lexer(buffer);
			free(buffer);
			if (!begin_lexicon)
				return ;
			mini = parser(&begin_lexicon);
			ft_lstclear(&begin_lexicon, &lst_del);
			display(mini.commands); //line to delete
			free_cmd(mini.commands);
		}
	}
}

int	main(void)
{
	launch_shell();
	return (0);
}
