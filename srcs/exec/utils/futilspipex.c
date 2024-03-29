/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futilspipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:30:16 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:25:42 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"
#include <termios.h>
#include "../../../incs/parsing.h"

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
	return (0);
}

int	ft_pipe2(t_mini *mini, int i, t_pipex *p, int *j)
{
	if (ft_isbuiltin(mini->commands[i]) == 1)
	{
		if (ft_builtinpipe(mini, mini->commands[i],
				mini->pipex, i) == -1)
			return (-1);
	}
	if (i == 0 && ft_isbuiltin(mini->commands[i]) == 0)
	{
		if (ft_first_pipe(mini, p) == -1)
			return (-1);
	}
	if (i != mini->nbc - 1 && i != 0 && ft_isbuiltin(mini->commands[i]) == 0)
	{
		if (ft_pipechild(mini, i, j, p) == -1)
			return (-1);
	}
	if (i == mini->nbc - 1 && i != 0 && ft_isbuiltin(mini->commands[i]) == 0)
	{
		if (ft_last_pipe(mini, i, p) == -1)
			return (-1);
	}
	return (0);
}

int	ft_startinit(t_mini *mini, int *i)
{
	int	j;

	j = ft_init_pipex(mini, *i);
	while (j != 0 && *i <= mini->nbc - 1)
	{
		if (errno < 3 || errno == 11)
			return (ft_error(*i, mini, j));
		if (errno >= 3 && errno != 11)
			ft_error(*i, mini, j);
		*i = *i + 1;
		if (*i <= mini->nbc - 1)
			j = ft_init_pipex(mini, *i);
	}
	if (mini->nbc == 1 && *i < mini->nbc
		&& ft_isbuiltin(mini->commands[*i]) == 1)
	{
		if (ft_builtin(mini, mini->commands[*i], mini->pipex) == -1
			&& errno < 3)
			return (ft_error(*i, mini, 0));
		errno = 0;
		ft_closefour(mini);
	}
	return (0);
}

void	ft_waitstart(t_mini *mini)
{
	int	k;
	int	i;

	k = 0;
	i = errno;
	while (k < mini->nbc)
	{
		while (mini->pid[k] == -1)
			k++;
		waitpid(mini->pid[k], &g_exitstatus, 0);
		if (WIFSIGNALED(mini->pid[k]))
		{
			if (g_exitstatus != 131)
				g_exitstatus += 128;
		}
		g_exitstatus = g_exitstatus % 256;
		k++;
	}
	errno = i;
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
