/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:05:30 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/26 16:10:33 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"
#include "../../incs/parsing.h"

long long	ft_atoiexit(char *cmd)
{
	long long	number;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	number = 0;
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
	while ((cmd[i] >= 9 && cmd[i] <= 13) || cmd[i] == 32)
		i++;
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
	free_mini(mini);
	ft_termios_ctl(mini);
	ft_signal_default();
	ft_freeenvp((mini->envp), (mini->envpl));
	exit(g_exitstatus);
}

void	ft_quit(t_mini *mini)
{
	if (mini->pipex)
		write(mini->pipex->errfile, "exit\n", 5);
	else
		write(2, "exit\n", 5);
	free_mini(mini);
	ft_termios_ctl(mini);
	ft_signal_default();
	ft_freeenvp((mini->envp), (mini->envpl));
	exit(g_exitstatus);
}

int	ft_exit(t_mini *mini, char **cmd, int n)
{
	long long	exitnum;

	if (n != -1)
	{
		g_exitstatus = n;
		ft_quit(mini);
	}
	if (cmd == NULL || cmd[1] == NULL)
		ft_quit(mini);
	exitnum = ft_atoiexit(cmd[1]);
	if (exitnum == -1 || cmd[1][0] == '\0')
		ft_errorexit(mini, cmd[1]);
	if (cmd[2] != NULL)
	{
		ft_errorexit2(mini);
		return (-1);
	}
	g_exitstatus = exitnum % 256;
	ft_quit(mini);
	return (0);
}
