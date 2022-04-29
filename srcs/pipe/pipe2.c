/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:48:29 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/29 12:09:06 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_first_pipe2(t_mini *mini, t_pipex *pipex)
{
	if (pipex->infile == -1 && pipex->outfile != -1)
	{
		if (dup2(pipex->outfile, 1) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (pipex->infile != -1 && pipex->outfile != -1)
	{
		if (dup2(pipex->infile, 0) == -1)
			return (ft_seterrno(11));
		if (dup2(pipex->outfile, 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * mini->nbc +1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

int	ft_first_pipe(t_mini *mini, t_pipex *pipex)
{
	if (pipex->infile == -1 && pipex->outfile == -1)
	{
		if (mini->nbc != 1)
		{
			if (dup2(pipex->tube[1], 1) == -1)
				return (ft_seterrno(11));
		}
		if (close(pipex->tube[0]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (pipex->infile != -1 && pipex->outfile == -1)
	{
		if (ft_utilsfirstpipe(mini, pipex) == -1)
			return (-1);
		exit(0);
	}
	ft_first_pipe2(mini, pipex);
	ft_seterrno(12);
	return (-1);
}

int	ft_last_pipe2(t_mini *mini, int i, t_pipex *pipex)
{
	if (pipex->infile == -1 && pipex->outfile != -1)
	{
		if (dup2(pipex->tube[2 * i - 2], 0) == -1)
			return (ft_seterrno(11));
		if (dup2(pipex->outfile, 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (pipex->infile != -1 && pipex->outfile != -1)
	{
		if (dup2(pipex->infile, 0) == -1)
			return (ft_seterrno(11));
		if (dup2(pipex->outfile, 1) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

int	ft_last_pipe(t_mini *mini, int i, t_pipex *pipex)
{
	if (pipex->infile == -1 && pipex->outfile == -1)
	{
		if (dup2(pipex->tube[2 * i - 2], 0) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (pipex->infile != -1 && pipex->outfile == -1)
	{
		if (dup2(pipex->infile, 0) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	ft_last_pipe2(mini, i, pipex);
	ft_seterrno(12);
	return (-1);
}
