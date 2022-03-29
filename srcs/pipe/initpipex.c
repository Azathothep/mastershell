/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:08:54 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/29 11:47:47 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

static char	*ft_freetab(char **tab)
{
	int	i;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_initpath(int	*i, t_list *envpl)
{
	char	**tab;
	t_list	*temp;

	*i = 0;
	temp = envpl;
	while (temp != NULL && ft_strncmp("PATH=", temp->content, 5) != 0)
	{
		*i = *i + 1;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		errno = 2;
		return (NULL);
	}
	tab = ft_split(temp->content + 5, ':');
	if (tab == NULL)
	{
		errno = 1;
		return (NULL);
	}
	*i = 0;
	return (tab);
}

char	*ft_path(char *cmd, t_list *envpl)
{
	int		i;
	char	**tab;
	char	*path;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	tab = ft_initpath(&i, envpl);
	if (tab == NULL)
		return (NULL);
	while (tab[i] != NULL)
	{
		path = ft_joinpath(tab, cmd, i);
		if (path == NULL)
			return (ft_freetab(tab));
		if (access(path, X_OK) == 0)
		{
			ft_freetab(tab);
			return (path);
		}
		free(path);
		i++;
	}
	errno = 3;
	return (ft_freetab(tab));
}

int	ft_init_pipex(t_mini *mini, int i)
{
	int	j;

	j = 0;
	mini->pipex->cmd = mini->commands[i];
	free(mini->pipex->path);
	mini->pipex->path = ft_path(mini->pipex->cmd[0], mini->envpl);
	if (mini->pipex->path == NULL)
		return (-1);
	if (mini->infile != NULL)
	{
		j = ft_init_files(mini, i);
	}
	if (mini->infile == NULL)
	{
		mini->pipex->infile = -1;
		mini->pipex->outfile = -1;
	}
	if (j != 0)
		return (j);
	//free(mini->envp); a corriger et remettre
	mini->envp = ft_convert(mini->envpl);
	if (mini->envp == NULL)
		return (-1);
	return (0);
}
