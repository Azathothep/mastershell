/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:08:54 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/19 16:01:18 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_puthere(t_mini *mini, t_pipex *p, int i)
{
	t_list	*t;
	int		pid;

	pid = fork();
	if (pid == -1)
		return (ft_seterrno(11));
	if (pid == 0)
		ft_puthere2(mini, &t, i, p);
	waitpid(pid, NULL, 0);
	if (i != 0)
		p->infile = p->tube[2 * i - 2];
	if (i == 0)
		p->infile = p->tube[2 * mini->nbc];
	return (0);
}

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

char	*ft_path(char *cmd, t_list *envpl, t_mini *mini)
{
	int		i;
	char	**tab;
	char	*path;

	if (access(cmd, X_OK) == 0 && ft_testdirectory(cmd) != -1)
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
	ft_seterrnopath(mini, cmd);
	return (ft_freetab(tab));
}

int	ft_init_pipex(t_mini *mini, int i)
{
	int	j;

	j = 0;
	errno = 1;
	if (i >= mini->nbc)
		return (0);
	mini->pipex->cmd = mini->commands[i];
	free(mini->pipex->path);
	mini->pipex->path = NULL;
	ft_initthings(mini->pipex);
	j = ft_init_files(mini, i);
	if (j != 0)
		return (ft_closefiles(mini, j, i));
	if (ft_isbuiltin(mini->pipex->cmd) == 0)
		mini->pipex->path = ft_path(mini->pipex->cmd[0], mini->envpl, mini);
	if (ft_isbuiltin(mini->pipex->cmd) == 1)
		mini->pipex->path = ft_strdup("ok");
	if (mini->pipex->path == NULL)
		return (ft_closefiles(mini, -1, i));
	ft_freeenvin(&(mini->envp));
	mini->envp = ft_convert(mini->envpl);
	if (mini->envp == NULL)
		return (ft_closefiles(mini, -1, i));
	errno = 0;
	return (0);
}
