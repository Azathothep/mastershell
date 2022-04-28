/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:35 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/28 13:47:18 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

void	ft_freeenvp(char ***envp, t_list **envpl)
{
	int	i;

	i = 0;
	if (*envpl != NULL)
		ft_lstclear(envpl, free);
	if (*envp != NULL)
	{
		while ((*envp)[i] != NULL)
		{
			free((*envp)[i]);
			i++;
		}
	}
	free(*envp);
}

void	ft_freehere(t_list ***heredoc, int nbc)
{
	int	i;

	i = 0;
	if (*heredoc != NULL)
	{
		while (i < nbc)
		{
			if ((*heredoc)[i] != NULL)
				ft_lstclear((heredoc)[i], &free);
			i++;
		}
	}
	free(*heredoc);
}

void	ft_freeinout(t_inout **file, int nbc)
{
	int	i;

	i = 0;
	if (*file != NULL)
	{
		while (i < nbc)
		{
			ft_lstclear(&((*file)[i].files), &free);
			i++;
		}
	}
	free(*file);
}

void	ft_freepipex(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->pipex != NULL)
	{
		free(mini->pipex->tube);
		while (mini->pipex->cmd[i] != NULL)
		{
			free(mini->pipex->cmd[i]);
			i++;
		}
		free(mini->pipex->cmd);
		free(mini->pipex->path);
	}
	free(mini->pipex);
}

int	ft_freeall(t_mini *mini)
{
	free(mini->pid);
	free(mini->infhere);
	ft_freepipex(mini);
	ft_freeinout(&(mini->infile), mini->nbc);
	ft_freeinout(&(mini->outfile), mini->nbc);
	ft_freeinout(&(mini->errfile), mini->nbc);
	ft_freehere(&(mini->heredocs), mini->nbc);
	ft_freeenvp(&(mini->envp), &(mini->envpl));
	ft_freecommands(&(mini->commands));
	return (0);
}
