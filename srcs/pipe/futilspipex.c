/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futilspipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:30:16 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/29 10:39:04 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_pipechild(t_mini *mini, int i, int *j, t_pipex *p)
{
	if (p->infile == -1 && p->outfile == -1)
		*j = ft_child(mini, 0, i, p);
	if (p->infile != -1 && p->outfile == -1)
		*j = ft_child(mini, 1, i, p);
	if (p->infile == -1 && p->outfile != -1)
		*j = ft_child(mini, 2, i, p);
	if (p->infile != -1 && p->outfile != -1)
		*j = ft_child(mini, 3, i, p);
	if (*j == -1)
		return (-1);
}

int	ft_pipe2(t_mini *mini, int i, t_pipex *p, int *j)
{
	if (ft_isbuiltin(mini->commands[i]) == 1)
	{
		if (ft_builtinpipe(mini, mini->commands[i],
				mini->pipex, i) == -1)
			return (-1);
	}
	if (i == 0)
	{
		if (ft_first_pipe(mini, p) == -1)
			return (-1);
	}
	if (i != mini->nbc - 1 && i != 0)
	{
		if (ft_pipechild(mini, i, j, p) == -1)
			return (-1);
	}
	if (i == mini->nbc - 1 && i != 0)
	{
		if (ft_last_pipe(mini, i, p) == -1)
			return (-1);
	}
}

int	ft_startinit(t_mini *mini, int *i)
{
	int	j;

	j = ft_init_pipex(mini, *i);
	while (j != 0 && *i <= mini->nbc - 1)
	{
		if (errno < 3 || errno == 11)
			return (ft_error(*i, mini, j, 0));
		if (errno >= 3 && errno != 11)
			ft_error(*i, mini, j, 1);
		*i = *i + 1;
		j = ft_init_pipex(mini, *i);
	}
	if (mini->nbc == 1 && *i < mini->nbc
		&& ft_isbuiltin(mini->commands[*i]) == 1)
	{
		if (ft_builtin(mini, mini->commands[*i], mini->pipex) == -1
			&& errno < 3)
			return (ft_error(*i, mini, 0, 0));
	}
	return (0);
}

void	ft_waitstart(t_mini *mini)
{
	int	k;

	k = 0;
	while (k < mini->nbc)
	{
		while (mini->pid[k] == -1)
			k++;
		waitpid(mini->pid[k], NULL, 0);
		status_child(mini, mini->pid[k]);
		k++;
	}
	ft_freeall(mini);
}

void	ft_puthere2(t_mini *mini, t_list **t, int i, t_pipex *p)
{
	*t = ft_lstlast(mini->heredocs[i]);
	if (i != 0)
	{
		if (close(p->tube[2 * i]) == -1)
			exit(2);
		write(p->tube[2 * i - 1], (*t)->content, ft_strlen((*t)->content));
	}
	if (i == 0)
	{
		if (close(p->tube[2 * mini->nbc]) == -1)
			exit(2);
		write(p->tube[2 * mini->nbc + 1], (*t)->content,
			ft_strlen((*t)->content));
	}
	exit(0);
}
