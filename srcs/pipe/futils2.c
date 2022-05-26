/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:09:12 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/26 12:19:04 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_testdirectory(char *cmd)
{
	int		i;
	int		j;
	char	test[2];

	if (ft_strncmp("minishell", cmd, 11) == 0)
		return (-1);
	i = open(cmd, O_RDONLY);
	if (i == -1)
	{
		errno = 0;
		return (-1);
	}
	j = read(i, test, 2);
	if (j == -1)
	{
		errno = 0;
		return (-1);
	}
	return (0);
}

void	status_child(t_mini *mini, int pid)
{
	mini += 0;
	if (WIFEXITED(pid))
		exitstatus = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		exitstatus = WTERMSIG(pid);
		//if (exitstatus != 131)
		//	exitstatus += 128;
	}
}

int	ft_seterr(t_mini *mini, int i)
{
	mini->pipex->errfile = 2;
	return (i);
}
