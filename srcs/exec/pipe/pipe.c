/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:59:42 by rmonacho          #+#    #+#             */
/*   Updated: 2022/07/19 15:40:04 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"
#include <termios.h>
#include "../../../incs/parsing.h"

int	ft_child2(t_mini *mini, int mode, int i, t_pipex *pipex)
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

int	ft_child(t_mini *mini, int mode, int i, t_pipex *pipex)
{
	if (mode == 0)
	{
		if (dup2(pipex->tube[2 * i - 2], 0) == -1
			|| dup2(pipex->tube[2 * i + 1], 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i]) == -1
			|| close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (mode == 1)
	{
		if (dup2(pipex->infile, 0) == -1
			|| dup2(pipex->tube[2 * i + 1], 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i]) == -1
			|| close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (ft_child2(mini, mode, i, pipex))
		return (-1);
	return (0);
}

int	ft_pipex(t_mini *mini, int i, t_pipex *p)
{
	int	j;

	if (ft_initpipestart(mini, i, &j) == -1)
		return (-1);
	if (mini->pid[i] == 0)
	{
		if (mini->infhere[i] == 1)
		{
			if (ft_puthere(mini, mini->pipex, i) == -1)
				return (-1);
		}
		if (ft_nexthere(mini, i) == -1)
		{
			if (ft_pipe2(mini, i, p, &j) == -1)
				return (-1);
		}
		if (ft_nexthere(mini, i) == 1)
		{
			if (ft_pipehere(mini, i, p) == -1)
				return (-1);
		}
	}
	if (ft_endpipe(mini, i, p) == -1)
		return (-1);
	return (0);
}

int	ft_start_pipe(t_mini *mini)
{
	int	i;

	ft_initspace(&i, mini);
	if (ft_init_start(mini) == -1)
		return (ft_error(i, mini, 0));
	while (mini->commands[i] != NULL)
	{
		while (mini->commands[i] == NULL && i < mini->nbc)
			i++;
		if (ft_startinit(mini, &i) == -1)
			return (-1);
		while (mini->commands[i] == NULL && i < mini->nbc)
			i++;
		if (i < mini->nbc && (mini->nbc != 1
				|| (mini->nbc == 1 && ft_isbuiltin(mini->commands[i]) == 0)))
		{
			if (ft_pipex(mini, i, mini->pipex) == -1
				&& (errno == 1 || errno == 11))
				return (ft_error(i, mini, 0));
		}
		if (i < mini->nbc)
			i++;
	}
	ft_waitstart(mini);
	return (0);
}
