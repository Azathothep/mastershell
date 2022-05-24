/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:02:45 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/19 16:16:46 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

char	**ft_convert2(char **envp)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i] != NULL)
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	temp[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		temp[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		i++;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		temp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (temp);
}

t_list	*ft_convlist(char **envp)
{
	int		i;
	t_list	*envpl;
	t_list	*temp;

	i = 0;
	envpl = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		temp = ft_lstnew(ft_strdup(envp[i]));
		if (temp == NULL)
		{
			errno = 1;
			return (NULL);
		}
		ft_lstadd_back(&envpl, temp);
		i++;
	}
	return (envpl);
}

static char	*ft_freetab2(char **tab)
{
	int	i;

	errno = 0;
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	errno = 1;
	return (NULL);
}

int	ft_init_start(t_mini *mini)
{
	int	j;

	j = 0;
	mini->pipex = malloc(sizeof(t_pipex));
	if (mini->pipex == NULL)
		return (ft_seterrno(1));
	mini->pipex->path = NULL;
	if (ft_inittube(mini, mini->pipex) == 1)
		return (-1);
	ft_freetabenv(mini);
	if (mini->envpl != NULL)
		mini->envp = ft_convert(mini->envpl);
	if (mini->envpl == NULL)
		mini->envp = ft_convert2(mini->envp);
	ft_freelistenv(mini);
	mini->envpl = ft_convlist(mini->envp);
	if (mini->envpl == NULL)
		return (-1);
	mini->pid = malloc(sizeof(int) * mini->nbc);
	if (mini->pid == NULL)
		return (ft_seterrno(1));
	while (j < mini->nbc)
		mini->pid[j++] = 0;
	return (0);
}

char	*ft_joinpath(char **tab, char *cmd, int i)
{
	char	*path;
	char	*temp;
	int		j;

	j = 0;
	while (tab[i][j] != '\0')
			j++;
	if (tab[i][j - 1] != '/')
	{
		temp = ft_strjoin(tab[i], "/");
		if (temp == NULL)
			return (ft_freetab2(tab));
		path = ft_strjoin(temp, cmd);
		if (path == NULL)
			return (ft_freetab2(tab));
		free(temp);
	}
	else
		path = ft_strjoin(tab[i], cmd);
	if (path == NULL)
		return (ft_freetab2(tab));
	return (path);
}
