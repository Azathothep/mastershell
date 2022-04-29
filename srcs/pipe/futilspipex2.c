/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futilspipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:40:13 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/29 10:59:17 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"
#include <termios.h>
#include "../../incs/parsing.h"

int	ft_utilsfirstpipe(t_mini *mini, t_pipex *pipex)
{
	if (mini->nbc != 1)
	{
		if (dup2(pipex->tube[1], 1) == -1)
			return (ft_seterrno(11));
	}
	if (dup2(pipex->infile, 0) == -1)
		return (ft_seterrno(11));
	if (close(pipex->tube[0]) == -1
		|| close(pipex->tube[2 * mini->nbc + 1]) == -1)
		return (ft_seterrno(11));
	if (execve(pipex->path, pipex->cmd, mini->envp) == -1)
		return (ft_seterrno(11));
}

int	ft_endpipe(t_mini *mini, int i, t_pipex *p)
{
	ft_signal_silence();
	if (i == 0)
	{
		if (close(p->tube[mini->nbc * 2 + 1]) == -1)
			return (ft_seterrno(11));
	}
	if (ft_close(mini, i) == -1)
		return (-1);
	ft_init_signals_interactive();
}

int	ft_initpipestart(t_mini *mini, int i, int *j)
{
	ft_signal_default();
	mini->pid[i] = fork();
	*j = 0;
	if (mini->pid[i] == -1)
		return (ft_seterrno(11));
}
