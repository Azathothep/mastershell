/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:41:47 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/21 16:00:40 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_seterrnocd(char *last, int mode)
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
			errno = 18;
		return (-1);
	}
	free(last);
	return (-1);
}

char	*ft_getpwd(void)
{
	char	*buf;

	buf = malloc(sizeof(char) * (PATH_MAX + 1));
	if (buf == NULL)
	{
		ft_seterrno(1);
		return (NULL);
	}
	buf[PATH_MAX] = '\0';
	buf = getcwd(buf, PATH_MAX);
	if (buf == NULL)
	{
		if (errno == EACCES)
			errno = 14;
		else
			errno = 18;
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
		if (ft_strncmp(temp->content, "OLDPWD=", 7) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin("OLDPWD=", lastpath);
			if (temp->content == NULL)
				return (ft_seterrno(1));
			return (0);
		}
		temp = temp->next;
	}
	temp = ft_lstnew(ft_strjoin("OLDPWD=", lastpath));
	if (temp == NULL)
		return (ft_seterrno(1));
	ft_lstadd_back(&(mini->envpl), temp);
	return (0);
}

int	ft_changepwd(t_mini *mini, char *name)
{
	t_list	*temp;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "PWD=", 4) == 0)
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
	if (cmd[1] == NULL || ft_strncmp(cmd[1], "~/", 3) == 0
		|| ft_strncmp(cmd[1], "~", 2) == 0
		|| ft_strncmp(cmd[1], "--", 3) == 0)
	{
		path = ft_ishome(mini, cmd[1]);
		if (path == NULL)
			return (ft_seterrno(13));
	}
	lastpath = ft_getpwd();
	if (lastpath == NULL)
		return (-1);
	if (path == NULL)
	{
		if (ft_fill(mini, cmd[1], &path) == -1)
			return (-1);
	}
	if (chdir(path) == -1)
		return (ft_seterrnocd(lastpath, 1));
	if (ft_oldpwd(mini, lastpath) == -1)
		return (ft_seterrnocd(lastpath, 2));
	free(lastpath);
	lastpath = ft_getpwd();
	if (lastpath == NULL)
		return (-1);
	if (ft_changepwd(mini, lastpath) == -1)
		return (ft_seterrnocd(lastpath, 2));
	return (0);
}
