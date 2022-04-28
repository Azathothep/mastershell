/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:59:42 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/28 15:00:52 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"
#include <termios.h>
#include "../../incs/parsing.h"

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

	ft_signal_default();
	mini->pid[i] = fork();
	j = 0;
	if (mini->pid[i] == -1)
		return (ft_seterrno(11));
	if (mini->pid[i] == 0)
	{
		if (mini->infhere[i] == 1)
		{
			if (ft_puthere(mini, mini->pipex, i) == -1)
				return (-1);
		}
		if (ft_nexthere(mini, i) == -1)
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
				if (p->infile == -1 && p->outfile == -1)
					j = ft_child(mini, 0, i, p);
				if (p->infile != -1 && p->outfile == -1)
					j = ft_child(mini, 1, i, p);
				if (p->infile == -1 && p->outfile != -1)
					j = ft_child(mini, 2, i, p);
				if (p->infile != -1 && p->outfile != -1)
					j = ft_child(mini, 3, i, p);
				if (j == -1)
					return (-1);
			}
			if (i == mini->nbc - 1 && i != 0)
			{
				if (ft_last_pipe(mini, i, p) == -1)
					return (-1);
			}
		}
		if (ft_nexthere(mini, i) == 1)
		{
			if (ft_pipehere(mini, i, p) == -1)
				return (-1);
		}
	}
	ft_signal_silence();
	if (i == 0)
	{
		if (close(p->tube[mini->nbc * 2 + 1]) == -1)
			return (ft_seterrno(11));
	}
	if (ft_close(mini, i) == -1)
		return (-1);
	ft_init_signals_interactive();
	return (0);
}

int	ft_start_pipe(t_mini *mini)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	errno = 0;
	k = 0;
	ft_init_signals_interactive();
	if (ft_init_start(mini) == -1)
		return (ft_error(i, mini, 0, 0));
	while (mini->commands[i] != NULL)
	{
		j = ft_init_pipex(mini, i);
		while (j != 0 && i <= mini->nbc - 1)
		{
			if (errno < 3 || errno == 11)
				return (ft_error(i, mini, j, 0));
			if (errno >= 3 && errno != 11)
				ft_error(i, mini, j, 1);
			i++;
			j = ft_init_pipex(mini, i);
		}
		if (mini->nbc == 1 && i < mini->nbc
			&& ft_isbuiltin(mini->commands[i]) == 1)
		{
			if (ft_builtin(mini, mini->commands[i], mini->pipex) == -1
				&& errno < 3)
				return (ft_error(i, mini, 0, 0));
		}
		else if (i < mini->nbc)
		{
			if (ft_pipex(mini, i, mini->pipex) == -1
				&& (errno == 1 || errno == 11))
				return (ft_error(i, mini, 0, 0));
		}
		i++;
	}
	while (k < mini->nbc)
	{
		while (mini->pid[k] == -1)
			k++;
		waitpid(mini->pid[k], NULL, 0);
		status_child(mini, mini->pid[k]);
		k++;
	}
	ft_freeall(mini);
	return (0);
}
