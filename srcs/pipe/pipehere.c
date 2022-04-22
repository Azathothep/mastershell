/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipehere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:18:47 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/22 14:47:36 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_nexthere(t_mini *mini, int i)
{
	if (i == mini->nbc - 1)
		return (-1);
	if (mini->infhere[i + 1] == 0)
		return (-1);
	else
		return (1);
}

int	ft_pipehere(t_mini *mini, int i, t_pipex *p)
{
	int	j;

	j = 0;
	if (ft_isbuiltin(mini->commands[i]) == 1)
	{
		if (ft_builtinpipehere(mini, mini->commands[i],
				mini->pipex) == -1)
			return (-1);
	}
	if (i == 0)
	{
		if (ft_first_pipeh(mini, p) == -1)
			return (-1);
	}
	if (i != mini->nbc - 1 && i != 0)
	{
		if (p->infile == -1 && p->outfile == -1)
			j = ft_childh(mini, 0, i, p);
		if (p->infile != -1 && p->outfile == -1)
			j = ft_childh(mini, 1, i, p);
		if (p->infile == -1 && p->outfile != -1)
			j = ft_childh(mini, 2, i, p);
		if (p->infile != -1 && p->outfile != -1)
			j = ft_childh(mini, 3, i, p);
		if (j == -1)
			return (-1);
	}
	return (0);
}

int	ft_child2h(t_mini *mini, int mode, int i, t_pipex *pipex)
{
	if (mode == 2)
	{
		if (dup2(pipex->tube[2 * i - 2], 0) == -1
			|| dup2(pipex->outfile, 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i]) == -1
			|| close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (mode == 3)
	{
		if (dup2(pipex->infile, 0) == -1 || dup2(pipex->outfile, 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i]) == -1
			|| close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

int	ft_childh(t_mini *mini, int mode, int i, t_pipex *pipex)
{
	if (mode == 0)
	{
		if (dup2(pipex->tube[2 * i - 2], 0) == -1
			|| dup2(pipex->tube[(2 * mini->nbc) - 1], 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[(2 * mini->nbc) - 2]) == -1
			|| close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (mode == 1)
	{
		if (dup2(pipex->infile, 0) == -1
			|| dup2(pipex->tube[(2 * mini->nbc) - 1], 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[(2 * mini->nbc) - 2]) == -1
			|| close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (ft_child2h(mini, mode, i, pipex))
		return (-1);
	return (0);
}
