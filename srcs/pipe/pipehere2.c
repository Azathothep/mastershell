/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipehere2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:30:19 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/29 14:11:42 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_first_pipe2h(t_mini *mini, t_pipex *pipex)
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
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

int	ft_first_pipeh(t_mini *mini, t_pipex *pipex)
{
	if (pipex->infile == -1 && pipex->outfile == -1)
	{
		if (mini->nbc != 1)
		{
			if (dup2(pipex->tube[(2 * mini->nbc) - 1], 1) == -1)
				return (ft_seterrno(11));
		}
		if (close(pipex->tube[(2 * mini->nbc) - 2]) == -1)
			return (ft_seterrno(11));
		if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
			return (ft_seterrno(11));
	}
	if (pipex->infile != -1 && pipex->outfile == -1)
	{
		if (ft_utils2pipehere(mini, pipex) == -1)
			return (-1);
	}
	ft_first_pipe2h(mini, pipex);
	return (-1);
}
