/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:41:47 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/28 11:15:56 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

int	ft_seterrnocd(char **path, char **last, int mode)
{
	if (mode == 1)
	{
		if (errno == EACCES)
			errno = 14;
		else if (errno == ENAMETOOLONG)
			errno = 15;
		else if (errno == ENOENT)
			errno = 16;
		else if (errno == ENOTDIR)
			errno = 17;
		else
			errno = 24;
	}
	free(*path);
	free(*last);
	ft_setexit(0, 0);
	return (-1);
}

char	*ft_getpwd(void)
{
	char	*buf;
	char	*test;

	buf = malloc(sizeof(char) * (PATH_MAX + 1));
	if (buf == NULL)
	{
		ft_seterrno(1);
		return (NULL);
	}
	buf[PATH_MAX] = '\0';
	test = getcwd(buf, PATH_MAX);
	if (test == NULL)
	{
		if (errno == EACCES)
			errno = 14;
		else
			errno = 24;
		return (NULL);
	}
	return (buf);
}

int	ft_oldpwd(t_mini *mini, char *lastpath)
{
	t_list	*temp;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "OLDPWD", 7) == 0
			|| ft_strncmp(temp->content, "OLDPWD=", 7) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin("OLDPWD=", lastpath);
			if (temp->content == NULL)
				return (ft_seterrno(1));
			return (0);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_changepwd(t_mini *mini, char *name)
{
	t_list	*temp;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "PWD", 4) == 0
			|| ft_strncmp(temp->content, "PWD=", 4) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin("PWD=", name);
			if (temp->content == NULL)
				return (ft_seterrno(1));
			return (0);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_cd(t_mini *mini, char **cmd)
{
	char	*path;
	char	*lastpath;

	path = NULL;
	lastpath = NULL;
	if (ft_cd2(mini, &path, cmd, &lastpath) == -1 && (errno == 1 || errno == 0))
	{
		free(path);
		return (ft_setexit(1, -1));
	}
	if (chdir(path) == -1)
	{
		ft_seterrnocd(&path, &lastpath, 1);
		return (ft_errorcd(mini, 4, cmd[1]));
	}
	if (ft_oldpwd(mini, lastpath) == -1)
		return (ft_seterrnocd(&path, &lastpath, 2));
	free(lastpath);
	lastpath = ft_getpwd();
	if (lastpath == NULL)
		return (ft_setexit(1, -1));
	if (ft_changepwd(mini, lastpath) == -1)
		return (ft_seterrnocd(&path, &lastpath, 2));
	ft_endcd(path, lastpath);
	return (0);
}
