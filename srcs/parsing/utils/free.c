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

#include "../../../incs/parsing.h"
#include "../../../incs/pipe.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_free(void *p)
{
	free (p);
	p = NULL;
	return (0);
}

void	free_inout(t_inout *inout, int nbc)
{
	int	i;

	i = -1;
	if (!inout)
		return ;
	while (++i < nbc)
	{
		ft_lstclear(&inout[i].files, &lst_del);
		ft_lstclear(&inout[i].types, &lst_del);
	}
	ft_free(inout);
}

void	free_mini(t_mini *mini)
{
	free_cmd(mini->commands);
	mini->commands = NULL;
	free_heredocs(mini->heredocs);
	mini->heredocs = NULL;
	free_inout(mini->infile, mini->nbc);
	mini->infile = NULL;
	free_inout(mini->outfile, mini->nbc);
	mini->outfile = NULL;
	free_inout(mini->errfile, mini->nbc);
	mini->errfile = NULL;
	free(mini->infhere);
	mini->infhere = NULL;
	free(mini->pid);
	mini->pid = NULL;
	ft_freepipex(mini);
	mini->pipex = NULL;
}

t_list	**free_heredocs(t_list **heredocs)
{
	int	i;

	i = -1;
	if (!heredocs || !*heredocs)
		return (NULL);
	while (heredocs[++i])
	{
		ft_lstclear(&(heredocs[i]), &lst_del);
	}
	ft_free(heredocs);
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
				ft_free(commands[i][j]);
			ft_free(commands[i]);
		}
		ft_free(commands);
		commands = NULL;
	}
	return (NULL);
}
