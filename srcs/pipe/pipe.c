/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:59:42 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/29 14:59:31 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

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

int	ft_pipex(t_mini *mini, int i, t_pipex *pipex)
{
	int	pid;
	int	j;

	pid = fork();
	j = 0;
	if (pid == -1)
	{
		errno = 11;
		return (-1);
	}
	if (pid == 0)
	{
		if (i == 0)
		{
			if (ft_first_pipe(mini, pipex) == -1)
			{
				return (-1);
			}
		}
		if (i != mini->nbc - 1 && i != 0)
		{
			if (pipex->infile == -1 && pipex->outfile == -1)
				j = ft_child(mini, 0, i, pipex);
			if (pipex->infile != -1 && pipex->outfile == -1)
				j = ft_child(mini, 1, i, pipex);
			if (pipex->infile == -1 && pipex->outfile != -1)
				j = ft_child(mini, 2, i, pipex);
			if (pipex->infile != -1 && pipex->outfile != -1)
				j = ft_child(mini, 3, i, pipex);
			if (j == -1)
				return (-1);
		}
		if (i == mini->nbc - 1)
		{
			if (ft_last_pipe(mini, i, pipex) == -1)
			{
				return (-1);
			}
		}
	}
	if (ft_close(mini, i) == -1)
	{
		return (-1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_start_pipe(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	errno = 0;
	if (ft_init_start(mini) == -1)
		return (ft_error(0, mini, 0));
	while (mini->commands[i] != NULL)
	{
		j = ft_init_pipex(mini, i);
		while (j != 0)
		{
			if (errno < 3)
				return (ft_error(i, mini, 0));
			if (errno >= 3)
				ft_error(i, mini, j);
			i++;
			j = ft_init_pipex(mini, i);
		}
		if (ft_isbuiltin(mini->commands[i]) == 1)
		{
			if (ft_builtin(mini, mini->commands[i], mini->pipex, i) == -1)
				return (ft_error(i, mini, 0));
		}
		else
		{
			if (ft_pipex(mini, i, mini->pipex) == -1)
			{
				return (ft_error(i, mini, 0));
			}
		}
		i++;
	}
	return (0);
}
