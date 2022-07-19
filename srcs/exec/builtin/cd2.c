/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:25:08 by rmonacho          #+#    #+#             */
/*   Updated: 2022/07/19 14:19:19 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

char	*ft_isold(t_mini *mini)
{
	t_list	*temp;
	char	*content;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "OLDPWD=", 7) == 0)
		{
			content = ft_strdup(temp->content + 7);
			if (content == NULL)
			{
				errno = 1;
				return (NULL);
			}
			write(mini->pipex->outfile, content, ft_strlen(content));
			write(mini->pipex->outfile, "\n", 1);
			return (content);
		}
		temp = temp->next;
	}
	errno = 18;
	return (NULL);
}

char	*ft_ishome(t_mini *mini, char *cmd)
{
	t_list	*temp;
	char	*content;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "HOME=", 5) == 0)
		{
			if (cmd != NULL && cmd[0] == '~')
				content = ft_strjoin(temp->content + 5, cmd + 1);
			else if (cmd != NULL)
				content = ft_strjoin(temp->content + 5, cmd + 2);
			else
				content = ft_strdup(temp->content + 5);
			if (content == NULL)
			{
				errno = 1;
				return (NULL);
			}
			return (content);
		}
		temp = temp->next;
	}
	errno = 13;
	return (NULL);
}

int	ft_cd2(t_mini *mini, char **path, char **cmd, char **lastpath)
{
	if (cmd[1] == NULL || ft_strncmp(cmd[1], "--", 3) == 0
		|| ft_strncmp(cmd[1], "~", 1) == 0)
	{
		*path = ft_ishome(mini, cmd[1]);
		if (*path == NULL)
			return (ft_errorcd(mini, 5, cmd[1]));
	}
	if (cmd[1] != NULL && ft_strncmp(cmd[1], "-", 2) == 0)
	{
		*path = ft_isold(mini);
		if (path == NULL)
			return (ft_errorcd(mini, 3, cmd[1]));
	}
	if (cmd[1] != NULL && cmd[1][0] == '\0')
		return (-1);
	if (*path == NULL)
		*path = ft_strdup(cmd[1]);
	if (*path == NULL)
		return (ft_seterrno(1));
	*lastpath = ft_getpwd();
	if (*lastpath == NULL)
		return (ft_errorcd(mini, 3, cmd[1]));
	return (0);
}

int	ft_errorcd2(t_mini *mini, char *cmd)
{
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
	if (mode == 4 && errno <= 17 && errno >= 14)
		ft_errorcd2(mini, cmd);
	if (mode == 5)
	{
		errno = 13;
		write(mini->pipex->errfile, "cd : HOME not set\n", 18);
	}
	ft_setexit(1, 0);
	return (-1);
}
