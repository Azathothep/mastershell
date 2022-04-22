/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:39:24 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/21 11:17:13 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_adderror(t_mini *mini, char *cmd, char c)
{
	t_list	*temp;

	if (c == '=')
	{
		if (ft_fullname(mini, cmd) == NULL)
			return (-1);
		return (0);
	}
	if (c == '\0')
	{
		temp = ft_lstnew(ft_strdup("\"\": not a valid identifier"));
		if (temp == NULL)
			return (ft_seterrno(1));
		ft_lstadd_back(&(mini->error), temp);
		return (0);
	}
	return (0);
}

char	*ft_copye(char *env)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	if (env[i] == '\0')
		return (ft_strdup(env));
	if (env[i] == '=')
	{
		temp = ft_strdup(env);
		temp[i + 1] = '\0';
	}
	return (temp);
}

int	ft_noarg(t_mini *mini, int fd)
{
	t_list	*temp;
	char	*temp2;

	temp = mini->envpl;
	while (temp != NULL)
	{
		write(fd, "declare -x ", 11);
		temp2 = ft_copye(temp->content);
		if (temp2[ft_strlen(temp2) - 1] == '=')
		{
			write(fd, temp2, ft_strlen(temp2));
			write(fd, "\"", 1);
			write(fd, temp->content + ft_strlen(temp2),
				ft_strlen(temp->content + ft_strlen(temp2)));
			write(fd, "\"", 1);
		}
		else
			write(fd, temp2, ft_strlen(temp2));
		temp = temp->next;
		write(fd, "\n", 1);
		free(temp2);
	}
	return (0);
}

int	ft_add(t_mini *mini, char *cmd)
{
	t_list	*temp;

	if (ft_parseexp(cmd) == '=' || ft_parseexp(cmd) == '\0')
	{
		if (ft_adderror(mini, cmd, ft_parseexp(cmd)) == -1)
			return (-1);
		return (ft_seterrno(19));
	}
	if (ft_isin(mini, cmd) == 1)
	{
		if (ft_readd(mini, cmd) == -1)
			return (ft_seterrno(1));
		return (0);
	}
	temp = ft_lstnew(ft_strdup(cmd));
	if (temp == NULL)
		return (ft_seterrno(1));
	ft_lstadd_back(&(mini->envpl), temp);
	return (0);
}

int	ft_export(t_mini *mini, char **cmd, t_pipex *pipex)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	if (cmd[1] == NULL)
	{
		if (ft_noarg(mini, pipex->outfile) == -1)
			return (-1);
		return (0);
	}
	while (cmd[i] != NULL)
	{
		j = ft_add(mini, cmd[i]);
		if (j == -1)
			k = -1;
		if (j == -1 && errno == 1)
			return (-1);
		i++;
	}
	if (k == -1)
		return (-1);
	else
		return (0);
}
