/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:49:35 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/26 14:43:32 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_setpipehere(t_mini *mini, t_pipex *pipex)
{
	if (pipex->outfile == -1)
	{
		pipex->outfile = pipex->tube[(2 * mini->nbc) - 1];
		if (dup2(pipex->tube[(2 * mini->nbc) - 1], 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[(2 * mini->nbc) - 2]) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

int	ft_builtinpipehere(t_mini *mini, char **cmd, t_pipex *pipex)
{
	if (ft_setpipehere(mini, pipex) == -1)
		return (-1);
	if (ft_strncmp("echo", cmd[0], 5) == 0)
		ft_echo(cmd, pipex);
	if (ft_strncmp("cd", cmd[0], 3) == 0)
		ft_cd(mini, cmd);
	if (ft_strncmp("pwd", cmd[0], 4) == 0)
		ft_pwd(mini, mini->pipex);
	if (ft_strncmp("export", cmd[0], 7) == 0)
		ft_export(mini, cmd, pipex);
	if (ft_strncmp("unset", cmd[0], 6) == 0)
		ft_unset(mini, cmd, pipex);
	if (ft_strncmp("env", cmd[0], 4) == 0)
		ft_env(mini);
	if (ft_strncmp("exit", cmd[0], 5) == 0)
		ft_exit(mini, cmd);
	exit(0);
	return (0);
}

int	ft_setpipe(t_mini *mini, t_pipex *pipex, int i)
{
	if (pipex->outfile == -1 && i != mini->nbc - 1)
	{
		pipex->outfile = pipex->tube[2 * i + 1];
		if (dup2(pipex->tube[2 * i + 1], 1) == -1)
			return (ft_seterrno(11));
		if (close(pipex->tube[2 * i]) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

int	ft_builtinpipe(t_mini *mini, char **cmd, t_pipex *pipex, int i)
{
	if (ft_setpipe(mini, pipex, i) == -1)
		return (-1);
	if (ft_strncmp("echo", cmd[0], 5) == 0)
		ft_echo(cmd, pipex);
	if (ft_strncmp("cd", cmd[0], 3) == 0)
		ft_cd(mini, cmd);
	if (ft_strncmp("pwd", cmd[0], 4) == 0)
		ft_pwd(mini, mini->pipex);
	if (ft_strncmp("export", cmd[0], 7) == 0)
		ft_export(mini, cmd, pipex);
	if (ft_strncmp("unset", cmd[0], 6) == 0)
		ft_unset(mini, cmd, pipex);
	if (ft_strncmp("env", cmd[0], 4) == 0)
		ft_env(mini);
	if (ft_strncmp("exit", cmd[0], 5) == 0)
		ft_exit(mini, cmd);
	exit(0);
	return (0);
}
