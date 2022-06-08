/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:37:58 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:23:24 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

static int	ft_max(char *content, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i] != '\0' && content[i] != '=')
		i++;
	while (cmd[j] != '\0')
		j++;
	if (j <= i)
		return (i);
	if (j > i)
		return (j);
	return (0);
}

static int	ft_init(t_mini *mini, char *cmd, t_list **temp, t_list **temp2)
{
	*temp = mini->envpl;
	*temp2 = mini->envpl;
	if (ft_strncmp((*temp)->content, cmd, ft_max((*temp)->content, cmd)) == 0)
	{
		free((*temp)->content);
		mini->envpl = (*temp)->next;
		free(*temp);
		return (0);
	}
	return (1);
}

int	ft_removeenv(t_mini *mini, char *cmd)
{
	t_list	*temp;
	t_list	*temp2;

	if (ft_init(mini, cmd, &temp, &temp2) == 0)
		return (0);
	temp = temp->next;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, cmd, ft_max(temp->content, cmd)) == 0)
		{
			free(temp->content);
			temp2->next = temp->next;
			free(temp);
			return (0);
		}
		temp = temp->next;
		temp2 = temp2->next;
	}
	return (0);
}

static int	ft_parse(char *cmd, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
		{
			write(pipex->errfile, "unset : \"", 9);
			write(pipex->errfile, cmd, ft_strlen(cmd));
			write(pipex->errfile, "\" : not a valid identifier\n", 27);
			return (ft_seterrno(22));
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_mini *mini, char **cmd, t_pipex *pipex)
{
	int	i;

	i = 1;
	while (cmd[i] != NULL)
	{
		if (ft_parse(cmd[i], pipex) != -1)
		{
			if (ft_removeenv(mini, cmd[i]) == -1)
				return (ft_setexit(1, -1));
		}
		i++;
	}
	ft_setexit(0, 0);
	return (0);
}
