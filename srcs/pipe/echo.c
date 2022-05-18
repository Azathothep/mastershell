/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:20:34 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/17 14:24:31 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_isoption(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (1);
	if (cmd[i] != '-' || (cmd[0] == '-' && cmd[1] == '\0'))
		return (1);
	i++;
	while (cmd[i] && cmd[i] == 'n')
		i++;
	if (cmd[i] == '\0')
		return (0);
	return (1);
}

void	ft_write(char *cmd, int *i, t_pipex *pipex)
{
	write(pipex->outfile, cmd, ft_strlen(cmd));
	write(pipex->outfile, " ", 1);
	*i = *i + 1;
}

int	ft_checkarg(char **cmd)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	k = 0;
	while (cmd[i] && cmd[i][j] && cmd[i][0] == '-')
	{
		j++;
		while (cmd[i][j] && cmd[i][j] == 'n')
		{
			k = 1;
			j++;
		}
		if (cmd[i][j] != '\0')
			return (i);
		j = 0;
		i++;
	}
	if (cmd[i] == NULL && k == 1)
		return (i);
	if (cmd[i] == NULL && k == 0)
		return (-1);
	return (i);
}

int	ft_echo(char **cmd, t_pipex *pipex)
{
	int	i;

	if (pipex->outfile == -1)
		pipex->outfile = 1;
	i = ft_checkarg(cmd);
	if (i == -1)
	{
		if (cmd[1] != NULL && cmd[1][0] == '-' && cmd[1][1] == '\0')
			write(pipex->outfile, "-", 1);
		write(pipex->outfile, "\n", 1);
		return (0);
	}
	if (cmd[i] == NULL)
		return (0);
	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		write(pipex->outfile, "- ", 2);
	while (cmd[i + 1] != NULL)
		ft_write(cmd[i], &i, pipex);
	if (cmd[i] != NULL)
		write(pipex->outfile, cmd[i], ft_strlen(cmd[i]));
	if (ft_isoption(cmd[1]) == 1)
		write(pipex->outfile, "\n", 1);
	return (0);
}
