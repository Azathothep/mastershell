/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:56:18 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:24:34 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"
#include "../../../incs/parsing.h"

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
