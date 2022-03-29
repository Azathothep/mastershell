/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:13:28 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/24 15:57:07 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_isbuiltin(char **cmd)
{
	if (ft_strncmp("echo", cmd[0], 4) == 0)
		return (1);
	/*if (ft_strncmp("cd", cmd[0], 2) == 0)
		return (1);
	if (ft_strncmp("pwd", cmd[0], 3) == 0)
		return (1);
	if (ft_strncmp("export", cmd[0], 6) == 0)
		return (1);
	if (ft_strncmp("unset", cmd[0], 5) == 0)
		return (1);
	if (ft_strncmp("env", cmd[0], 3) == 0)
		return (1);
	if (ft_strncmp("exit", cmd[0], 4) == 0)
		return (1);*/
	return (0);
}

int	ft_builtin(t_mini *mini, char **cmd, t_pipex *pipex, int i)
{
	(void)mini;
	if (ft_strncmp("echo", cmd[0], 4) == 0)
		ft_echo(cmd, pipex, i);
	/*if (ft_strncmp("cd", cmd[0], 2) == 0)
		ft_cd(mini, cmd);
	if (ft_strncmp("pwd", cmd[0], 3) == 0)
		ft_pwd(mini, cmd, i, mini->pipex);
	if (ft_strncmp("export", cmd[0], 6) == 0)
		ft_export(mini, cmd, pipex);
	if (ft_strncmp("unset", cmd[0], 5) == 0)
		ft_unset(mini, cmd, pipex);
	if (ft_strncmp("env", cmd[0], 3) == 0)
		ft_env(mini, cmd, pipex);
	if (ft_strncmp("exit", cmd[0], 4) == 0)
		ft_exit(mini, cmd, pipex);*/
	return (0);
}

int	ft_echo(char **cmd, t_pipex *pipex, int j)
{
	int	i;

	i = 1;
	if (pipex->outfile == -1)
		pipex->outfile = pipex->tube[2 * j + 1];
	close(pipex->tube[2 * j]);
	if (ft_strncmp(cmd[i], "-n", 2) == 0)
		i++;
	while (cmd[i + 1] != NULL)
	{
		write(pipex->outfile, cmd[i], ft_strlen(cmd[i]));
		write(pipex->outfile, " ", 1);
		i++;
	}
	write(pipex->outfile, cmd[i], ft_strlen(cmd[i]));
	if (ft_strncmp(cmd[1], "-n", 2) != 0)
		write(pipex->outfile, "\n", 1);
	return (0);
}

/*int	ft_cd(t_mini *mini, char **cmd)
{
}

int	ft_pwd(t_mini *mini, char **cmd, int j, t_pipex *pipex)
{
	int		i;

	i = 0;
	if (pipex->outfile == -1)
		pipex->outfile = pipex->tube[2 * i + 1];
	close(pipex->tube[2 * i]);
	while (mini->envpl != NULL
		&& ft_strncmp(mini->envpl->content, "PWD=", 4) != 0)
		mini->envpl = mini->envpl->next;
	if (mini->envpl == NULL)
		return (-1);
	write(pipex->outfile, mini->envpl->content + 4,
		ft_strlen(mini->envpl->content) - 4);
	write(pipex->outfile, "\n", 1);
}
*/