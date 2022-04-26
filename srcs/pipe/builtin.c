/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:13:28 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/25 15:26:00 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_isbuiltin(char **cmd)
{
	if (ft_strncmp("echo", cmd[0], 5) == 0)
		return (1);
	if (ft_strncmp("cd", cmd[0], 3) == 0)
		return (1);
	if (ft_strncmp("pwd", cmd[0], 4) == 0)
		return (1);
	if (ft_strncmp("export", cmd[0], 7) == 0)
		return (1);
	if (ft_strncmp("unset", cmd[0], 6) == 0)
		return (1);
	if (ft_strncmp("env", cmd[0], 4) == 0)
		return (1);
	if (ft_strncmp("exit", cmd[0], 5) == 0)
		return (1);
	return (0);
}

int	ft_builtin(t_mini *mini, char **cmd, t_pipex *pipex)
{
	int	j;

	j = 0;
	if (pipex->outfile == -1)
		pipex->outfile = 1;
	if (ft_strncmp("echo", cmd[0], 5) == 0)
		ft_echo(cmd, pipex);
	if (ft_strncmp("cd", cmd[0], 3) == 0)
		j = ft_cd(mini, cmd);
	if (ft_strncmp("pwd", cmd[0], 4) == 0)
		j = ft_pwd(mini, mini->pipex);
	if (ft_strncmp("export", cmd[0], 7) == 0)
		j = ft_export(mini, cmd, pipex);
	if (ft_strncmp("unset", cmd[0], 6) == 0)
		j = ft_unset(mini, cmd, pipex);
	if (ft_strncmp("env", cmd[0], 4) == 0)
		j = ft_env(mini);
	if (ft_strncmp("exit", cmd[0], 5) == 0)
		j = ft_exit(mini, cmd);
	return (0);
}
