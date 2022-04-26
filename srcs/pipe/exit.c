/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:05:30 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/26 15:44:24 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

long long	ft_atoiexit(char *cmd)
{
	long long	number;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	while ((cmd[i] >= 9 && cmd[i] <= 13) || cmd[i] == 32)
		i++;
	if (cmd[i] == '-' || cmd[i] == '+')
	{
		if (cmd[i] == '-')
			sign *= -1;
		i++;
	}
	while (cmd[i] >= '0' && cmd[i] <= '9')
	{
		number = number * 10 + (cmd[i] - '0');
		i++;
	}
	if (cmd[i] != '\0')
		return (ft_seterrno(20));
	return (number * sign);
}

void	ft_errorexit2(t_mini *mini)
{
	write(mini->pipex->errfile, "exit\n", 5);
	write(mini->pipex->errfile, "exit : too many arguments\n", 26);
	errno = 21;
}

void	ft_errorexit(t_mini *mini, char *cmd)
{
	write(mini->pipex->errfile, "exit\n", 5);
	write(mini->pipex->errfile, "exit : ", 7);
	write(mini->pipex->errfile, cmd, ft_strlen(cmd));
	write(mini->pipex->errfile, " : numeric argument required\n", 29);
	//ft_free_all(mini);
	exit(mini->exit_status);
}

void	ft_quit(t_mini *mini)
{
	//ft_free_all(mini);
	write(mini->pipex->errfile, "exit\n", 5);
	exit(mini->exit_status);
}

int	ft_exit(t_mini *mini, char **cmd)
{
	long long	exitnum;

	if (cmd[1] == NULL)
		ft_quit(mini);
	exitnum = ft_atoiexit(cmd[1]);
	if (exitnum == -1 || cmd[1][0] == '\0')
		ft_errorexit(mini, cmd[1]);
	if (cmd[2] != NULL)
	{
		ft_errorexit2(mini);
		return (-1);
	}
	mini->exit_status = exitnum % 256;
	ft_quit(mini);
	return (0);
}
