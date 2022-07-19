/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:19:38 by rmonacho          #+#    #+#             */
/*   Updated: 2022/07/19 15:14:15 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

int	ft_isin2(t_mini *mini, t_list **temp, int *i, char *cmd)
{
	*i = ft_checkequal(cmd);
	*temp = mini->envpl;
	if (ft_strchr(cmd, '=') != NULL)
	{
		while (*temp != NULL)
		{
			if (ft_strncmp((*temp)->content, cmd, *i) == 0)
			{
				if (((char *)(*temp)->content)[*i + 1] == '\0'
					|| ((char *)(*temp)->content)[*i] == '=')
					return (1);
			}
			*temp = (*temp)->next;
		}
	}
	return (0);
}

int	ft_checkequal(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
		i++;
	return (i);
}

int	ft_readd(t_mini *mini, char *cmd)
{
	char	*name;
	t_list	*temp;

	name = ft_strdup(cmd);
	if (name == NULL)
		return (ft_seterrno(1));
	temp = mini->envpl;
	if (cmd[ft_checkequal(cmd)] == '\0')
		return (ft_freechar(name, 0));
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, cmd, ft_checkequal(cmd)) == 0)
		{
			if (((char *)(temp->content))[ft_checkequal(cmd)] == '\0'
				|| ((char *)(temp->content))[ft_checkequal(cmd)] == '=')
			{
				free(temp->content);
				temp->content = name;
				return (0);
			}
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

int	ft_isin(t_mini *mini, char *cmd)
{
	t_list	*temp;
	int		i;

	if (ft_isin2(mini, &temp, &i, cmd) == 1)
		return (1);
	if (ft_strchr(cmd, '=') == NULL)
	{
		while (temp != NULL)
		{
			if (ft_strncmp(temp->content, cmd, i) == 0)
			{
				if (((char *)temp->content)[i] == '\0'
					|| ((char *)temp->content)[i] == '=')
					return (1);
			}
			temp = temp->next;
		}
	}
	return (-1);
}

char	ft_parseexp(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '\0')
		return ('\0');
	if (cmd[0] == '=')
		return ('=');
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
			return ('=');
		i++;
	}
	return ('n');
}
