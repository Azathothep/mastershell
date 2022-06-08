/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futilspipehere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:54:03 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:25:35 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

int	ft_utilspipehere(t_mini *mini, t_pipex *p, int i, int *j)
{
	if (p->infile == -1 && p->outfile == -1)
		*j = ft_childh(mini, 0, i, p);
	if (p->infile != -1 && p->outfile == -1)
		*j = ft_childh(mini, 1, i, p);
	if (p->infile == -1 && p->outfile != -1)
		*j = ft_childh(mini, 2, i, p);
	if (p->infile != -1 && p->outfile != -1)
		*j = ft_childh(mini, 3, i, p);
	if (*j == -1)
		return (-1);
	return (0);
}

int	ft_utils2pipehere(t_mini *mini, t_pipex *pipex)
{
	if (mini->nbc != 1)
	{
		if (dup2(pipex->tube[(2 * mini->nbc) - 1], 1) == -1)
			return (ft_seterrno(11));
	}
	if (dup2(pipex->infile, 0) == -1)
		return (ft_seterrno(11));
	if (close(pipex->tube[(2 * mini->nbc) - 2]) == -1)
		return (ft_seterrno(11));
	if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
		return (ft_seterrno(11));
	return (0);
}
