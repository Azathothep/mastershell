/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:09:12 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/28 15:00:03 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

void	status_child(t_mini *mini, int pid)
{
	if (WIFEXITED(pid))
		mini->exit_status = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		mini->exit_status = WTERMSIG(pid);
		if (mini->exit_status != 131)
			mini->exit_status += 128;
	}
}

int	ft_seterr(t_mini *mini, int i)
{
	mini->pipex->errfile = 2;
	return (i);
}