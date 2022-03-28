/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:58:06 by marvin            #+#    #+#             */
/*   Updated: 2022/03/21 14:58:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdlib.h>
#include <stdio.h>

void	free_mini(t_mini *mini)
{
	free_cmd(mini->commands);
	free_heredocs(mini->heredocs);
	free(mini->infile);
	free(mini->outfile);
	mini->parse_error = 0;
	mini->error = 0;
	return ;
}

t_list	**free_heredocs(t_list **heredocs)
{
	int	i;

	i = -1;
	while (heredocs[++i])
	{
		ft_lstclear(&heredocs[i], &lst_del);
	}
	free(heredocs);
	return (NULL);
}

char	**free_tabtwo(char **tab)
{
	int	index;

	index = -1;
	if (!tab)
		return (NULL);
	while (tab[++index])
		free(tab[index]);
	free(tab);
	tab = NULL;
	return (NULL);
}

char	***free_cmd(char ***commands)
{
	int	i;
	int	j;

	i = -1;
	if (commands)
	{
		while (commands[++i])
		{
			j = -1;
			while (commands[i][++j])
				free(commands[i][j]);
			free(commands[i]);
		}
		free(commands);
		commands = NULL;
	}
	return (NULL);
}

void	lst_del(void *content)
{
	free((char *)content);
}
