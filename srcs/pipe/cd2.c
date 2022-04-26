/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:25:08 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/26 15:43:33 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_errorcd2(t_mini *mini, int mode, char *cmd)
{
	(void)mode;
	write(mini->pipex->errfile, "cd : ", 5);
	if (errno == 14)
	{
		write(mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, " permission denied\n", 19);
	}
	else if (errno == 15)
	{
		write(mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, " file name too long\n", 20);
	}
	else if (errno == 16)
	{
		write(mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, " no such file or directory\n", 27);
	}
	else if (errno == 17)
	{
		write(mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, " is not a directory\n", 20);
	}
	else if (errno == 18)
		write (mini->pipex->errfile, "OLDPWD not set\n", 15);
	return (0);
}

int	ft_errorcd(t_mini *mini, int mode, char *cmd)
{
	if (mode == 1)
	{
		write(mini->pipex->errfile, "cd : ", 5);
		write (mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, ": No such file or directory\n", 28);
		errno = 16;
	}
	if (mode == 3 && errno == 14)
	{
		write(mini->pipex->errfile, "cd : ", 5);
		write (mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, ": Permission denied\n", 20);
	}
	if (mode == 3 && errno == 18)
		write(mini->pipex->errfile, "cd : OLDPWD not set\n", 20);
	if (mode == 4)
		ft_errorcd2(mini, mode, cmd);
	if (mode == 5)
	{
		errno = 13;
		write(mini->pipex->errfile, "cd : HOME not set\n", 18);
	}
	return (-1);
}

int	ft_fill(t_mini *mini, char *cmd, char **path)
{
	t_list	*temp;

	temp = mini->envpl;
	if (cmd[0] == '-')
	{
		if (cmd[1] != '\0')
			return (ft_errorcd(mini, 1, cmd));
		while (temp != NULL)
		{
			if (ft_strncmp(temp->content, "OLDPWD", 6) == 0)
			{
				*path = ft_strdup(temp->content);
				if (*path == NULL)
					return (ft_seterrno(1));
				return (0);
			}
			temp = temp->next;
		}
		return (ft_errorcd(mini, 2, cmd));
	}
	*path = ft_strdup(cmd);
	if (*path == NULL)
		return (ft_seterrno(1));
	return (0);
}

char	*ft_ishome(t_mini *mini, char *cmd)
{
	t_list	*temp;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "HOME=", 5) == 0)
			return (ft_strdup(temp->content + 5));
		temp = temp->next;
	}
	if ((cmd[0] == '-' && cmd[1] == '-' && cmd[2] == '\0')
		|| (cmd[0] == '~' && cmd[1] == '\0')
		|| (cmd[0] == '~' && cmd[1] == '/' && cmd[2] == '\0'))
		return (ft_strdup("/Users/rmonacho"));
	return (NULL);
}
